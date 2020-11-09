#include "awebp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Awebp w;

    w.show();

    return a.exec();
}
