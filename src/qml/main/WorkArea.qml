import QtQuick 2.5
import QtQuick.Controls 1.4
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
            var posPortString = message.lastIndexOf("Port")
            if (posPortString > 0) {
                var port = message.substr(posPortString + 5, 5)
                webSocket.url = "ws://localhost:" + port
                webSocket.active = true
            }
        }
    }

    WebSocket {
        id: webSocket
        active: true
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
    }
}
