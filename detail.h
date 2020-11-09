#ifndef DETAIL_H
#define DETAIL_H

#include <QMainWindow>

class Detail : public QWidget {
Q_OBJECT

public:
Detail(QWidget *parent = nullptr, QStringList fs = QStringList());
QStringList fileNames;

signals:



private:
void showEvent(QShowEvent *event) override;
void closeEvent(QCloseEvent *event) override;
};

#endif // DETAIL_H
