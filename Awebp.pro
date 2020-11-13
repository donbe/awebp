QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += WEBP_HAVE_PNG

SOURCES += \
    form.cpp \
    imageio/image_dec.c \
    imageio/image_enc.c \
    imageio/imageio_util.c \
    imageio/jpegdec.c \
    imageio/metadata.c \
    imageio/pngdec.c \
    imageio/pnmdec.c \
    imageio/tiffdec.c \
    imageio/webpdec.c \
    imageio/wicdec.c \
    main.cpp \
    awebp.cpp

HEADERS += \
    awebp.h \
    common.h \
    examples/unicode.h \
    form.h \
    imageio/image_dec.h \
    imageio/image_enc.h \
    imageio/imageio_util.h \
    imageio/jpegdec.h \
    imageio/metadata.h \
    imageio/pngdec.h \
    imageio/pnmdec.h \
    imageio/tiffdec.h \
    imageio/webpdec.h \
    imageio/wicdec.h

FORMS += \
    form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    awebp.qrc

# 手动添加的库
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

macx: LIBS += -L/usr/local/lib/ -lwebp
macx: LIBS += -L/usr/local/lib/ -lwebpdecoder
macx: LIBS += -L/usr/local/lib/ -lwebpdemux
macx: LIBS += -L/usr/local/lib/ -lwebpmux
macx: LIBS += -L/usr/local/lib/ -lpng
macx: LIBS += -L/usr/local/lib/ -ljpeg

macx: PRE_TARGETDEPS += /usr/local/lib/libwebp.a
macx: PRE_TARGETDEPS += /usr/local/lib/libwebpdecoder.a
macx: PRE_TARGETDEPS += /usr/local/lib/libwebpdemux.a
macx: PRE_TARGETDEPS += /usr/local/lib/libwebpmux.a
macx: PRE_TARGETDEPS += /usr/local/lib/libpng.a
macx: PRE_TARGETDEPS += /usr/local/lib/libjpeg.a

# 指定版本后，是不是低版本就用不了了
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

ICON = awebp.icns
