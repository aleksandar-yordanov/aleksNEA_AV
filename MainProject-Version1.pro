QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += console

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    /Users/aleks/Downloads/SQLAPI/include \
    /opt/homebrew/Cellar/asio/1.20.0/include \
    /opt/homebrew/Cellar/nlohmann-json/3.10.4/include

LIBS += \
    -L"/Users/aleks/Downloads/SQLAPI/lib" -lSQLAPI

SOURCES += \
    accountwindow.cpp \
    common.cpp \
    errorbox.cpp \
    httprequest.cpp \
    license.cpp \
    loginmanager.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    resetwindow.cpp \
    statsmanager.cpp \
    stringrequest.cpp \
    threattype.cpp

HEADERS += \
    accountwindow.h \
    common.h \
    errorbox.h \
    httprequest.h \
    includes.h \
    license.h \
    loginmanager.h \
    loginwindow.h \
    mainInherited.h \
    mainwindow.h \
    resetwindow.h \
    statsmanager.h \
    stringrequest.h \
    threattype.h

FORMS += \
    accountwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    resetwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
