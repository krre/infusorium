import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtWebSockets 1.0
import Aquarium 1.0
import "main"
import "../js/utils.js" as Utils
import "../js/settings.js" as Settings

ApplicationWindow {
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias webSocket: webSocket
    id: mainRoot
    title: APP.name
    width: 800
    height: 600
    visible: true

    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: Settings.load()

    function createObjInMainContext(url, properties) {
        Utils.createDynamicObject(mainRoot, url, properties ? properties : {})
    }

    onClosing: {
        Settings.save()
    }

    Net {
        id: net
    }

    WebSocket {
        id: webSocket
        url: String("ws://%1:%2").arg(SETTINGS.value("Infusoria", "address", "localhost")).arg(SETTINGS.value("Infusoria", "port", "51000"))
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

    SplitView {
        anchors.fill: parent

        TabView {
            id: tabView
            Layout.fillWidth: true
            frameVisible: false
        }

        ColumnLayout {
            id: infuTableContainer
            width: 150
            Layout.minimumWidth: 50
            spacing: 0

            TableView {
                id: infuTableView
                Layout.preferredWidth: parent.width
                Layout.fillHeight: true
                frameVisible: false

                TableViewColumn {
                    title: qsTr("Infusoria")
                }
            }

            RowLayout {
                Layout.preferredWidth: parent.width
                Layout.margins: 5

                Button {
                    Layout.fillWidth: true
                    text: qsTr("Attach")
                    enabled: infuTableView.currentRow >= 0
                }

                Button {
                    Layout.fillWidth: true
                    text: qsTr("Detach")
                    enabled: infuTableView.currentRow >= 0
                }
            }
        }
    }
}
