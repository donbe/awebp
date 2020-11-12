#include "awebp.h"

#include <QApplication>
#include <qfile.h>
#include <qdebug.h>
#include <QTextStream>
#include <QtDebug>
#include <QtGlobal>

#ifdef Q_OS_MAC
#include <syslog.h>
static void SYSLOG(const char *format, ...) {
    va_list vaList;
    va_start(vaList, format);
    vsyslog(LOG_ERR, format, vaList);
}

#else
static void SYSLOG(const char *format, ...) {
}

#endif


void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str) {
    const char *msg = str.toLatin1();
    switch (type) {
        case QtDebugMsg:
            SYSLOG("Debug: %s\n", msg);
            break;

        case QtInfoMsg:
            SYSLOG("Info: %s\n", msg);
            break;

        case QtWarningMsg:
            SYSLOG("Warning: %s\n", msg);
            break;

        case QtCriticalMsg:
            SYSLOG("Critical: %s\n", msg);
            break;
        case QtFatalMsg:
            SYSLOG("Fatal: %s\n", msg);
            abort();
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qInstallMessageHandler(myMessageHandler);

    Awebp w;
    w.show();

    return a.exec();
}
