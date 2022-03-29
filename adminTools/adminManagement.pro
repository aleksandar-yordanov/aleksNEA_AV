QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    /opt/homebrew/Cellar/asio/1.22.1/include \
    /opt/homebrew/Cellar/nlohmann-json/3.10.4/include

SOURCES += \
        httprequest.cpp \
        input.cpp \
        main.cpp \
        networkingmanager.cpp \
        stringrequest.cpp

HEADERS += \
    httprequest.h \
    includes.h \
    input.h \
    networkingmanager.h \
    stringrequest.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


