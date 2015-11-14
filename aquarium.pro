QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

include(../qosg/src/qosg.pri)

SOURCES += \
    src/cpp/main.cpp

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml \
    src/js/utils.js \
    src/qml/main/About.qml \
    src/qml/main/Options.qml

HEADERS += \
    src/cpp/global/app.h
