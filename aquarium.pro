QT += opengl qml quick

CONFIG += c++11
TEMPLATE = app

include(../qosg/src/qosg.pri)

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/global/settings.cpp \
    src/cpp/global/utils.cpp

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml \
    src/js/utils.js \
    src/qml/main/About.qml \
    src/qml/main/Options.qml \
    src/js/settings.js \
    src/qml/components/BrowseButton.qml \
    src/qml/components/filedialog/FileDialogBase.qml \
    src/qml/components/filedialog/FileDialogDirectory.qml \
    src/qml/components/filedialog/FileDialogOpen.qml \
    src/js/dialog.js \
    src/qml/components/WindowDialog.qml

HEADERS += \
    src/cpp/global/app.h \
    src/cpp/global/settings.h \
    src/cpp/global/utils.h
