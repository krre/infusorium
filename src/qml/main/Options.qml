import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import "../components"
import "../../js/dialog.js" as Dialog

WindowDialog {
    id: root
    title: qsTr("Options")
    width: 400
    height: 200

    onAccepted: {
        SETTINGS.setValue("Infusoria", "address", address.text)
        SETTINGS.setValue("Infusoria", "port", port.text)
    }

    ColumnLayout {
        width: parent.width

        GroupBox {
            title: "Infusoria Manager"
            Layout.preferredWidth: parent.width
            Layout.alignment: Qt.AlignHCenter

            GridLayout {
                width: parent.width
                columns: 2

                Label {
                    text: qsTr("Address:")
                }

                TextField {
                    id: address
                    Layout.fillWidth: true
                    text: SETTINGS.value("Infusoria", "address", "localhost")
                }

                Label {
                    text: qsTr("Port:")
                }

                TextField {
                    id: port
                    Layout.fillWidth: true
                    text: SETTINGS.value("Infusoria", "port", "51000")
                }
            }
        }
    }
}
