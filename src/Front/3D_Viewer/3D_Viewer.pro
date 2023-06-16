QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QtGifImage/src/3rdParty/giflib/dgif_lib.c \
    QtGifImage/src/3rdParty/giflib/egif_lib.c \
    QtGifImage/src/3rdParty/giflib/gif_err.c \
    QtGifImage/src/3rdParty/giflib/gif_font.c \
    QtGifImage/src/3rdParty/giflib/gif_hash.c \
    QtGifImage/src/3rdParty/giflib/gifalloc.c \
    QtGifImage/src/3rdParty/giflib/quantize.c \
    QtGifImage/src/gifimage/qgifimage.cpp \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \


HEADERS += \
    QtGifImage/src/3rdParty/giflib/gif_hash.h \
    QtGifImage/src/3rdParty/giflib/gif_lib.h \
    QtGifImage/src/3rdParty/giflib/gif_lib_private.h \
    QtGifImage/src/gifimage/qgifglobal.h \
    QtGifImage/src/gifimage/qgifimage.h \
    QtGifImage/src/gifimage/qgifimage_p.h \
    glview.h \
    mainwindow.h

LIBS += ../../viewer.a

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
