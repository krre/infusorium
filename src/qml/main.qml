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
    statusBar: StatusBar {
        Label {
            text: webSocket.status === WebSocket.Open ? qsTr("Connected to " + webSocket.url) : qsTr("Disconnected")
        }
    }

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
        url: String("ws://%1:%2").arg(SETTINGS.value("Infusoria", "address")).arg(SETTINGS.value("Infusoria", "port"))

        onStatusChanged: {
            if (status === WebSocket.Open) {
                var message = {}
                message.method = "onlineList"
                message.id = "aquarium"
                sendTextMessage(JSON.stringify(message))
            }
        }

        onTextMessageReceived: {
            print("Infusoria:", message)
            var obj = JSON.parse(message)
            if (obj) {
                if (obj.id && obj.id === "aquarium") {
                    if (obj.result) {
                        for (var i in obj.result) {
                            var path = obj.result[i]
                            infuModel.append({ name: UTILS.pathToBaseName(path) })
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: infuModel
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
                model: infuModel

                TableViewColumn {
                    title: qsTr("Infusoria")
                    role: "name"
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
