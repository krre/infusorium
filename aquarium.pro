QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

include(../qosg/src/qosg.pri)

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/global/settings.cpp

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml \
    src/js/utils.js \
    src/qml/main/About.qml \
    src/qml/main/Options.qml \
    src/js/settings.js

HEADERS += \
    src/cpp/global/app.h \
    src/cpp/global/settings.h
