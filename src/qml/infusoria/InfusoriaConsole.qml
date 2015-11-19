import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import Aquarium 1.0
import "../components"
import "../../js/files.js" as Files

WindowDialog {
    property string filePath
    property bool openAfterCreating: false
    title: qsTr("Infusoria Console")
    width: 600
    height: 400
    standardButtons: StandardButton.Close

    Component.onCompleted: {
        process.run(SETTINGS.value("Infusoria", "executable"), [filePath, "-n"])
    }

    Process {
        id: process
        onMessage: {
            textArea.append(message)
            if (openAfterCreating && message.lastIndexOf("created successfully") > 0) {
                Files.openFile(filePath)
            }
        }
    }

    TextArea {
        id: textArea
        anchors.fill: parent
    }
}
