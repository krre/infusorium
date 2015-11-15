import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../components"
import "../../js/dialog.js" as Dialog

WindowDialog {
    id: root
    title: qsTr("Options")
    width: 500
    height: 200

    onAccepted: {
        SETTINGS.setValue("Infusoria", "executable", executablePath.text)
        SETTINGS.setValue("Infusoria", "workspace", workspacePath.text)
    }

    ColumnLayout {
        width: parent.width

        GroupBox {
            title: "Infusoria"
            Layout.preferredWidth: parent.width
            Layout.alignment: Qt.AlignHCenter

            GridLayout {
                width: parent.width
                columns: 3

                Label {
                    text: qsTr("Executable:")
                }

                TextField {
                    id: executablePath
                    Layout.fillWidth: true
                    text: SETTINGS.value("Infusoria", "executable")
                }

                BrowseButton {
                    onClicked: {
                        var selectFileDialog = Dialog.selectFile(root)
                        selectFileDialog.accepted.connect(function() {
                            executablePath.text = UTILS.urlToPath(selectFileDialog.fileUrl)
                        })
                    }
                }

                Label {
                    text: qsTr("Workspace:")
                }

                TextField {
                    id: workspacePath
                    Layout.fillWidth: true
                    text: SETTINGS.value("Infusoria", "workspace", UTILS.homePath)
                }

                BrowseButton {
                    onClicked: {
                        var selectDirectoryDialog = Dialog.selectDirectory(root)
                        selectDirectoryDialog.accepted.connect(function() {
                            workspacePath.text = UTILS.urlToPath(selectDirectoryDialog.fileUrl)
                        })
                    }
                }
            }
        }
    }
}
