#ifndef AWEBP_H
#define AWEBP_H

#include <QMainWindow>
#include "qpushbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Awebp; }
QT_END_NAMESPACE

class Awebp : public QMainWindow
{
Q_OBJECT

public:
Awebp(QWidget *parent = nullptr);
~Awebp();

public slots:
void onClicked();

private:
Ui::Awebp *ui;
QWidget *mContent;
QPushButton *mButton;
void changeBackground();
void resizeEvent(QResizeEvent *event) override;

};
#endif // AWEBP_H
