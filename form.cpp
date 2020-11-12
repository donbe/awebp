#include "form.h"
#include "ui_form.h"
#include <qstandarditemmodel.h>
#include <qurl.h>
#include <QListView>
#include <qdebug.h>
#include "imageio/image_dec.h"
#include "imageio/imageio_util.h"
#include <QFileDialog>
#include <QMessageBox>




Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form) {
    ui->setupUi(this);
}

Form::Form(QWidget *parent, QStringList fs) : QWidget(parent),
    ui(new Ui::Form) {
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    fileNames = fs;

    ui->lineEdit->setValidator(new QIntValidator(0, 100, this) );
    ui->lineEdit_2->setValidator(new QIntValidator(0, 100, this) );

    // 列表数据
    QStandardItemModel *model = new QStandardItemModel(this);
    for (QString filename : fileNames) {
        model->appendRow(new QStandardItem(QIcon(filename), QUrl(filename).fileName()));
    }

    // 绑定数据
    QListView *listView = ui->listView;
    listView->setModel(model);

    // 按钮事件
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onClicked()));
}

void Form::onClicked() {

    int ok;
    int timestamp_ms = 0;
    int pic_num = 0;
    int duration = 1000 / ui->lineEdit->text().toInt();
    int width = 0, height = 0;
    int loop_count = ui->lineEdit_2->text().toInt();

    WebPAnimEncoder *enc = NULL;
    WebPData webp_data;
    WebPPicture pic;
    WebPAnimEncoderOptions anim_config;
    WebPConfig config;

    WebPDataInit(&webp_data);
    if (!WebPAnimEncoderOptionsInit(&anim_config) ||
        !WebPConfigInit(&config) ||
        !WebPPictureInit(&pic)) {
        qCritical("Library version mismatch!\n");
        ok = 0;
        goto End;
    }

    config.lossless = 1;

    // 验证config
    ok = WebPValidateConfig(&config);
    if (!ok) {
        qCritical("Invalid configuration.\n");
        goto End;
    }

    for (QString filename : fileNames) {
        pic.use_argb = 1;

        ok = ReadImage(filename.toLocal8Bit().data(), &pic);
        if (!ok) {
            qCritical("ReadImage fail.\n");
            goto End;
        }

        if (enc == NULL) {
            width = pic.width;
            height = pic.height;
            enc = WebPAnimEncoderNew(width, height, &anim_config);
            ok = (enc != NULL);
            if (!ok) {
                qCritical("Could not create WebPAnimEncoder object.\n");
            }
        }

        if (ok) {
            ok = (width == pic.width && height == pic.height);
            if (!ok) {
                qCritical("Frame #%d dimension mismatched! "
                          "Got %d x %d. Was expecting %d x %d.\n",
                          pic_num, pic.width, pic.height, width, height);
            }
        }

        if (ok) {
            ok = WebPAnimEncoderAdd(enc, &pic, timestamp_ms, &config);
            if (!ok) {
                qCritical("Error while adding frame #%d\n", pic_num);
            }
        }

        WebPPictureFree(&pic);
        if (!ok) {
            qCritical("Error while free frame #%d\n", pic_num);
            goto End;
        }

        timestamp_ms += duration;
        ++pic_num;
    }

    // add a last fake frame to signal the last duration
    ok = ok && WebPAnimEncoderAdd(enc, NULL, timestamp_ms, NULL);
    ok = ok && WebPAnimEncoderAssemble(enc, &webp_data);
    if (!ok) {
        qCritical("Error during final animation assembly.\n");
    }

 End:
    // free resources
    WebPAnimEncoderDelete(enc);

    if (ok && loop_count > 0) {  // Re-mux to add loop count.
        ok = SetLoopCount(loop_count, &webp_data);
        if (!ok) {
            qCritical("Error while set loop count\n");
        }
    }

    if (ok) {
        QString fileName = QFileDialog::getSaveFileName(this, "保存文件",
                                                        QDir::homePath() + "/Downloads/untitled.webp",
                                                        "Images (*.webp)");
        if (fileName.length()) {
            ok = ImgIoUtilWriteFile(fileName.toLocal8Bit().data(), webp_data.bytes, webp_data.size);
            if (!ok) {
                qCritical("Error while write file\n");
            }
        }
    }

    if(!ok){
        QMessageBox msgBox;
        msgBox.setText("提示");
        msgBox.setInformativeText("糟糕，合成失败了。");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

    WebPDataClear(&webp_data);
}

Form::~Form() {
    delete ui;
}

int Form::ReadImage(const char filename[], WebPPicture *const pic) {
    const uint8_t *data = NULL;
    size_t data_size = 0;
    WebPImageReader reader;
    int ok;
#ifdef HAVE_WINCODEC_H
    // Try to decode the file using WIC falling back to the other readers for
    // e.g., WebP.
    ok = ReadPictureWithWIC(filename, pic, 1, NULL);
    if (ok) return 1;

#endif
    if (!ImgIoUtilReadFile(filename, &data, &data_size)) return 0;

    reader = WebPGuessImageReader(data, data_size);
    ok = reader(data, data_size, pic, 1, NULL);
    free((void *)data);
    return ok;
}

int Form::SetLoopCount(int loop_count, WebPData *const webp_data) {
    int ok = 1;
    WebPMuxError err;
    uint32_t features;
    WebPMuxAnimParams new_params;
    WebPMux *const mux = WebPMuxCreate(webp_data, 1);
    if (mux == NULL) return 0;

    err = WebPMuxGetFeatures(mux, &features);
    ok = (err == WEBP_MUX_OK);
    if (!ok || !(features & ANIMATION_FLAG)) goto End;

    err = WebPMuxGetAnimationParams(mux, &new_params);
    ok = (err == WEBP_MUX_OK);
    if (ok) {
        new_params.loop_count = loop_count;
        err = WebPMuxSetAnimationParams(mux, &new_params);
        ok = (err == WEBP_MUX_OK);
    }

    if (ok) {
        WebPDataClear(webp_data);
        err = WebPMuxAssemble(mux, webp_data);
        ok = (err == WEBP_MUX_OK);
    }

 End:
    WebPMuxDelete(mux);
    if (!ok) {
        fprintf(stderr, "Error during loop-count setting\n");
    }

    return ok;
}

void Form::closeEvent(QCloseEvent *event) {
    awebp->show();
}
