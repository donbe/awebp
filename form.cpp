#include "form.h"
#include "ui_form.h"
#include <qstandarditemmodel.h>
#include <qurl.h>
#include <QListView>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form) {
    ui->setupUi(this);
}

Form::Form(QWidget *parent, QStringList fs) : QWidget(parent),
    ui(new Ui::Form) {
    ui->setupUi(this);

    fileNames = fs;

    ui->lineEdit->setValidator(new QIntValidator(0, 100, this) );
    ui->lineEdit_2->setValidator(new QIntValidator(0, 100, this) );

    // 列表数据
    QStandardItemModel *model = new QStandardItemModel(this);
    for (QString filename : fileNames) {
        model->appendRow(new QStandardItem(QIcon(filename), QUrl(filename).fileName()));
    }

    // 左侧列表
    QListView *listView = ui->listView;
    listView->setModel(model);
}

Form::~Form() {
    delete ui;
}
