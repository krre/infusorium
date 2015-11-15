import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "../components"
import "../../js/dialog.js" as Dialog

Window {
    id: root
    title: qsTr("Options")
    width: 500
    height: 200
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    modality: Qt.ApplicationModal

    onVisibleChanged: if (!visible) root.destroy()

    ColumnLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignHCenter
        spacing: 0

        ScrollView {
            id: scrollView
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            frameVisible: false

            ColumnLayout {
                x: 10
                width: scrollView.width - 20

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
                            text: UTILS.homePath
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

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Button {
                Layout.margins: 10
                Layout.rightMargin: 0
                text: qsTr("OK")
                onClicked: root.destroy()
            }

            Button {
                Layout.margins: 10
                Layout.leftMargin: 0
                text: qsTr("Cancel")
                onClicked: root.destroy()
            }
        }
    }
}
