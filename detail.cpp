#include "detail.h"
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qstandarditemmodel.h>
#include <qurl.h>
#include <QGroupBox>
#include "common.h"
#include <QLineEdit>

static const QString style = "";

Detail::Detail(QWidget *parent, QStringList fs) : QWidget(parent) {
    fileNames = fs;

    setMinimumWidth(700);
    setMinimumHeight(500);

    // 加载样式文件
    loadcss(this, ":/detail.css");

    // 横向布局
    QHBoxLayout *hlayout = new QHBoxLayout();
    setLayout(hlayout);


    // 列表数据
    QStandardItemModel *model = new QStandardItemModel(this);
    for (QString filename : fileNames) {
        model->appendRow(new QStandardItem(QIcon(filename), QUrl(filename).fileName()));
    }

    // 左侧列表
    QListView *listView = new QListView();
    listView->setModel(model);
    listView->setResizeMode(QListView::Adjust);
    listView->setMovement(QListView :: Static);
    listView->setIconSize(QSize(30, 30));
    hlayout->addWidget(listView);


    // 右侧设置
    QGroupBox *box = new QGroupBox();
    box->setTitle("输出设置");
    box->setMinimumWidth(200);
    hlayout->addWidget(box);

    QWidget *frequencyGroup = new QWidget(box);
    frequencyGroup->move(0,30);
    QHBoxLayout *frequencyLayout= new QHBoxLayout();
    frequencyGroup->setLayout(frequencyLayout);

    QLabel *label = new QLabel("帧频",frequencyGroup);
    frequencyLayout->addWidget(label);

    QLineEdit *edit = new QLineEdit(frequencyGroup);
    frequencyLayout->addWidget(edit);
    edit->resize(150,21);

}

void Detail::showEvent(QShowEvent *event) {
}

void Detail::closeEvent(QCloseEvent *event) {
}
