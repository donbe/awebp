#include "awebp.h"
#include "ui_awebp.h"
#include "qboxlayout.h"
#include <QDebug>
#include <QFileDialog>
#include "detail.h"


Awebp::Awebp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Awebp) {


    // 设置最小值
    setMinimumWidth(700);
    setMinimumHeight(500);

    // 设置背景色
    setStyleSheet("background-color:white;");

    // 容器
    mContent = new QWidget;
    setCentralWidget(mContent);

    // 添加按钮
    mButton = new QPushButton("点击导入图片", mContent);
    mButton->setCursor(Qt::PointingHandCursor);
    mButton->setStyleSheet("*{"
                           "border-style: dashed;"
                           "border-width: 2px;"
                           "border-radius: 5px;"
                           "color: rgb(97,97,97);"
                           "font-size: 15px;"
                           "font-weight: bold;"
                           "}"
                           "*:hover{"
                           "border-color: rgb(105,181,249);"
                           "}"
                           "*:!hover{"
                           "border-color: rgb(217,217,217);"
                           "}"
                           );

    connect(mButton, SIGNAL(clicked()), this, SLOT(onClicked()));
}

void Awebp::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    int bw = 300;
    int bh = 200;

    mButton->setGeometry((width() - bw) / 2, (height() - bh) / 2, bw, bh);
}

// 析构函数
Awebp::~Awebp() {
    delete ui;
    delete mContent;
}

void Awebp::onClicked() {
    QFileDialog dialog(this);

    dialog.setNameFilter("Images (*.png)"); // 设置后缀
    dialog.setFileMode(QFileDialog::ExistingFiles); // 设置可多选
    dialog.setDirectory(QDir::homePath()); // 设置打开默认目录

    QStringList fileNames;

    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        qInfo("%d", fileNames.length());

        Detail *detail = new Detail(nullptr,fileNames);
        detail->show();

        close();
    }


}
