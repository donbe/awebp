#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    Form(QWidget *parent = nullptr, QStringList fs = QStringList());
    ~Form();


    QStringList fileNames;
public slots:
    void onClicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
