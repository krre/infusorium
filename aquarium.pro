QT += opengl qml quick websockets

CONFIG += c++11
TEMPLATE = app

include(../qosg/src/qosg.pri)
include(../infusoria/src/common/common.pri)

SOURCES += \
    src/cpp/main.cpp \
    src/cpp/process.cpp \
    src/cpp/net/net.cpp

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
    src/qml/components/WindowDialog.qml \
    src/qml/components/messagedialog/MessageDialogBase.qml \
    src/qml/components/messagedialog/MessageDialogError.qml \
    src/qml/components/messagedialog/MessageDialogInformation.qml \
    src/qml/components/messagedialog/MessageDialogQuestion.qml \
    src/qml/components/messagedialog/MessageDialogWarning.qml \
    src/qml/main/WorkArea.qml \
    src/js/files.js \
    README.md

HEADERS += \
    src/cpp/process.h \
    src/cpp/net/net.h
