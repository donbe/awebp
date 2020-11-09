#include "detail.h"
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qstandarditemmodel.h>
#include <qurl.h>

Detail::Detail(QWidget *parent, QStringList fs) : QWidget(parent) {
    fileNames = fs;

    setMinimumWidth(700);
    setMinimumHeight(500);

    QHBoxLayout *hlayout = new QHBoxLayout();


//    QVBoxLayout *vrightRayout = new QVBoxLayout();


//    hlayout->addLayout(vrightRayout);

//    QPushButton *btn2 = new QPushButton("bbb");

//    btn2->setMaximumWidth(200);
//    btn2->setMinimumWidth(200);
//    vrightRayout->addWidget(btn2);



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
    QWidget *right = new QWidget();
    right->setStyleSheet("background-color:rgb(212,220,229)");
    right->setMinimumWidth(200);
    hlayout->addWidget(right);

    setLayout(hlayout);
}

void Detail::showEvent(QShowEvent *event) {
}

void Detail::closeEvent(QCloseEvent *event) {
}
