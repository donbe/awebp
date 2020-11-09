#include "detail.h"
#include <qdebug.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>

Detail::Detail(QWidget *parent) : QWidget(parent) {
    // 设置最小值
    setMinimumWidth(700);
    setMinimumHeight(500);

    QHBoxLayout *hlayout = new QHBoxLayout();

    QVBoxLayout *vleftLayout = new QVBoxLayout();
    QVBoxLayout *vrightRayout = new QVBoxLayout();

    hlayout->addLayout(vleftLayout);
    hlayout->addLayout(vrightRayout);

    QPushButton *btn1 = new QPushButton("aaa");
    QPushButton *btn2 = new QPushButton("bbb");
    btn2->setMaximumWidth(200);

    vleftLayout->addWidget(btn1);
    vrightRayout->addWidget(btn2);

    setLayout(hlayout);

}

void Detail::showEvent(QShowEvent *event) {

}

void Detail::closeEvent(QCloseEvent *event) {
}
