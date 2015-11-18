import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import Aquarium 1.0
import "../components"
import "../../js/files.js" as Files

WindowDialog {
    property string unitPath
    property bool openAfterCreating: false
    title: qsTr("Infusoria Console")
    width: 600
    height: 400
    standardButtons: StandardButton.Close

    Component.onCompleted: {
        process.run(SETTINGS.value("Infusoria", "executable"), [unitPath, "-n"])
    }

    Process {
        id: process
        onMessage: {
            textArea.append(message)
            if (message === "AI unit created successfully\n") {
                if (openAfterCreating && UTILS.isFileExists(unitPath)) {
                    Files.openUnit(unitPath)
                }
            }
        }
    }

    TextArea {
        id: textArea
        anchors.fill: parent
    }
}
