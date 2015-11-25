import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../components"
import "../../js/dialog.js" as Dialog
import "../../js/utils.js" as Utils

WindowDialog {
    id: root
    title: qsTr("New Infusoria File")
    width: 400
    height: 100

    onAccepted: {
        if (!name.text) {
            stayOnScreen = true
            Dialog.errorMessage(qsTr("Name is empty"))
        } else {
            var filePath = directory.text + "/" + name.text + ".infu"
            createObjInMainContext("qrc:/qml/infusoria/InfusoriaConsole.qml", { filePath: filePath, openAfterCreating: openAfterCreating.checked })
        }
    }

    GridLayout {
        width: parent.width
        columns: 2

        Label {
            text: qsTr("Name:")
        }

        TextField {
            id: name
            Layout.fillWidth: true
            Component.onCompleted: forceActiveFocus()
        }

        Label {
            text: qsTr("Directory:")
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: directory
                Layout.fillWidth: true
                text: SETTINGS.value("Infusoria", "workspace", UTILS.homePath)
            }

            BrowseButton {
                onClicked: {
                    var selectDirectoryDialog = Dialog.selectDirectory(root)
                    selectDirectoryDialog.accepted.connect(function() {
                        directory.text = UTILS.urlToPath(selectDirectoryDialog.fileUrl)
                    })
                }
            }
        }

        CheckBox {
            id: openAfterCreating
            text: qsTr("Open after creating")
            Layout.column: 1
            Layout.row: 2
            checked: true
        }
    }
}