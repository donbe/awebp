#include "awebp.h"

#include <QApplication>
#include <qfile.h>
#include <qdebug.h>



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Awebp w;
    w.show();

    return a.exec();
}
