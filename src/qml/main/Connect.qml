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
    }

    Connections {
        target: mainRoot.webSocket
        onStatusChanged: {
            if (status === WebSocket.Connecting) {
                statusTextArea.append(qsTr("Connecting to ") + mainRoot.webSocket.url)
            } else if (status === WebSocket.Open) {
                statusTextArea.append(qsTr("Open"))
                root.destroy()
            } else if (status === WebSocket.Closing) {
                statusTextArea.append(qsTr("Closing"))
            } else if (status === WebSocket.Closed) {
                statusTextArea.append(qsTr("Closed"))
            } else if (status === WebSocket.Error) {
                statusTextArea.append(qsTr("Error: ") + mainRoot.webSocket.errorString)
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
            text: SETTINGS.value("Infusoria", "address")
        }

        Label {
            text: qsTr("Port:")
        }

        TextField {
            id: port
            Layout.fillWidth: true
            text: SETTINGS.value("Infusoria", "port")
        }

        TextArea {
            id: statusTextArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
        }
    }
}
