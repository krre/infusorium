import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtWebSockets 1.0
import Aquarium 1.0

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath

    Component.onCompleted: {
        process.run(SETTINGS.value("Infusoria", "executable"), [filePath])
    }

    Component.onDestruction: process.shutdown()

    Process {
        id: process
        onMessage: {
            print("Process:", message)
        }
    }

    WebSocket {
        id: webSocket
        active: true
        url: "ws://localhost:" + SETTINGS.value("Infusoria", "port")
        onStatusChanged: {
            if (status === WebSocket.Connecting) {
                print("Connecting to url", url)
            } else if (status === WebSocket.Open) {
                print("Open connection")
            } else if (status === webSocket.Closed) {
                print("Closed connection")
            } else if (status === WebSocket.Error) {
                print("Error:", webSocket.errorString)
            }
        }
        onTextMessageReceived: print("Infusoria:", message)
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 7

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: sendTextField
                Layout.fillWidth: true
                Component.onCompleted: forceActiveFocus()
            }

            Button {
                text: "Send"
                onClicked: {
                    webSocket.sendTextMessage(sendTextField.text)
                    sendTextField.text = ""
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
