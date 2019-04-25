#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T13:56:38
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcpclient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=\
    receiver.cpp \
    senders.cpp \
    pkt.cpp \
    p2p.cpp \
    userUi.cpp \
    tcpclient.cpp \
    main.cpp


HEADERS  += \
    senders.h \
    receiver.h \
    pkt.h \
    p2p.h \
    userUi.h \
    tcpclient.h \
    msg_type.h

FORMS    += \
    tcpclient.ui \
    p2p.ui \
    receiver.ui \
    userUi.ui \
    senders.ui

#DISTFILES += \   qt_chat.pro.user \
#    tcpclient.pro.user \
#    background.jpg \
#    css/welcome.css \
#    img/Toolbar.bmp \
#    img/qt.png \
#    img/smile.ico

RESOURCES += \
    client.qrc
