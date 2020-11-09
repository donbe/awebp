#include <qstring.h>
#include <qfile.h>
#include <qwidget.h>

#ifndef COMMON_H
#define COMMON_H

inline void loadcss(QWidget *wgt, QString path){
    // 样式文件
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    wgt->setStyleSheet(styleSheet);
}

#endif // COMMON_H
