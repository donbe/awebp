#include "awebp.h"
#include "qboxlayout.h"
#include <QDebug>
#include <QFileDialog>
#include "form.h"
#include "common.h"


static const QString style = "";

Awebp::Awebp(QWidget *parent)
    : QMainWindow(parent) {
    loadcss(this, ":/awebp.css");

    // 设置最小值
    setMinimumWidth(700);
    setMinimumHeight(500);

    // 容器
    QWidget *content = new QWidget;
    setCentralWidget(content);

    // 添加按钮
    mButton = new QPushButton("点击导入图片", content);
    mButton->setCursor(Qt::PointingHandCursor);

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

}

void Awebp::onClicked() {
    QFileDialog dialog(this);

    dialog.setNameFilter("Images (*.png *.jpg *.jpeg)"); // 设置后缀
    dialog.setFileMode(QFileDialog::ExistingFiles); // 设置可多选
    dialog.setDirectory(QDir::homePath()); // 设置打开默认目录

    QStringList fileNames;

    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();

        Form *form = new Form(nullptr, fileNames);
        form->awebp = this;
        form->show();

        hide();
    }
}
