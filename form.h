#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <webp/types.h>
#include <webp/decode.h>
#include <webp/encode.h>
#include <webp/mux.h>

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

    int ReadImage(const char filename[], WebPPicture* const pic);
    int SetLoopCount(int loop_count, WebPData* const webp_data);


};

#endif // FORM_H
