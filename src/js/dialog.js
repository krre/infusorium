.import "../js/utils.js" as Utils

function selectFile(parent) {
    return Utils.createDynamicObject(parent, "qrc:/qml/components/filedialog/FileDialogOpen.qml")
}

function selectDirectory(parent) {
    return Utils.createDynamicObject(parent, "qrc:/qml/components/filedialog/FileDialogDirectory.qml")
}


