#include "awebp.h"
#include <QApplication>
#include <qdebug.h>


// 打印日志到系统控制台
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


// 输出stderr到日志文件
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

#ifdef QT_NO_DEBUG
    // 捕捉所有的qdebug信息到系统控制台
    qInstallMessageHandler(myMessageHandler);
    // 转发所有的stderr到日志文件中，只有app关掉后才会写文件
    freopen("/tmp/awebp.log", "a", stderr);
#endif

    Awebp w;
    w.show();

    return a.exec();
}
