.import "../js/utils.js" as Utils

function selectFile(parent, options) {
    return Utils.createDynamicObject(parent, "qrc:/qml/components/filedialog/FileDialogOpen.qml", options ? options : {})
}

function selectDirectory(parent) {
    return Utils.createDynamicObject(parent, "qrc:/qml/components/filedialog/FileDialogDirectory.qml")
}

function infoMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogInformation.qml", { text: message })
}

function warningMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogWarning.qml", { text: message })
}

function questionMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogQuestion.qml", { text: message })
}

function errorMessage(message) {
    return Utils.createDynamicObject(mainRoot, "qrc:/qml/components/messagedialog/MessageDialogError.qml", { text: message })
}
