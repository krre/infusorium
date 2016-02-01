import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtWebSockets 1.0
import "../components"

WindowDialog {
    id: root
    title: qsTr("Connect to IM")
    width: 400
    height: 200

    onAccepted: {
        stayOnScreen = true
        mainRoot.webSocket.active = false
        mainRoot.webSocket.active = true
        Settings.setValue("Common", "autoconnect", autoconnect.checked)
    }

    Connections {
        target: mainRoot.webSocket
        onStatusChanged: {
            if (status === WebSocket.Connecting) {
                statusTextArea.appendWithTime(qsTr("Connecting to ") + mainRoot.webSocket.url)
            } else if (status === WebSocket.Open) {
                statusTextArea.appendWithTime(qsTr("Open"))
                root.destroy()
            } else if (status === WebSocket.Closing) {
                statusTextArea.appendWithTime(qsTr("Closing"))
            } else if (status === WebSocket.Closed) {
                statusTextArea.appendWithTime(qsTr("Closed"))
            } else if (status === WebSocket.Error) {
                statusTextArea.appendWithTime(qsTr("Error: ") + mainRoot.webSocket.errorString)
                mainRoot.webSocket.active = false
            }
        }
    }

    GridLayout {
        anchors.fill: parent
        columns: 2

        Label {
            text: qsTr("Address:")
        }

        TextField {
            id: address
            Layout.fillWidth: true
            text: Settings.value("Infusoria", "address")
        }

        Label {
            text: qsTr("Port:")
        }

        TextField {
            id: port
            Layout.fillWidth: true
            text: Settings.value("Infusoria", "port")
        }

        CheckBox {
            id: autoconnect
            text: qsTr("Autoconnect")
            Layout.columnSpan: 2
            checked: Settings.value("Common", "autoconnect", false) === "true"
        }

        TextArea {
            id: statusTextArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            readOnly: true

            function appendWithTime(text) {
                var currentdate = new Date();
                var time = ((currentdate.getHours() < 10) ? "0" : "") + currentdate.getHours() + ":" +
                        ((currentdate.getMinutes() < 10) ? "0" : "") + currentdate.getMinutes() + ":" +
                        ((currentdate.getSeconds() < 10) ? "0" : "") + currentdate.getSeconds()
                append(time + ": " + text)
            }
        }
    }
}
