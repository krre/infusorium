QT += opengl qml quick websockets widgets

CONFIG += c++20
TEMPLATE = app

include(../infusoria/src/common/common.pri)

SOURCES += \
    src/cpp/Process.cpp \
    src/cpp/main.cpp

RESOURCES += \
    src/qml.qrc

DISTFILES += \
    src/qml/main.qml \
    src/qml/main/MainMenu.qml \
    src/js/utils.js \
    src/qml/main/About.qml \
    src/qml/main/Options.qml \
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
    README.md \
    src/qml/main/Connect.qml \
    src/qml/main/Logger.qml \
    src/js/infu-proto.js \
    src/qml/components/ButtonBase.qml

HEADERS += \
    src/cpp/Process.h
