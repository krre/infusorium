import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtWebSockets 1.0
import Infusorium 1.0
import "main"
import "../js/utils.js" as Utils
import "../js/infu-proto.js" as InfuProto

ApplicationWindow {
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias webSocket: webSocket
    property alias infuManager: infuManager
    property bool isConnected: webSocket.status === WebSocket.Open
    id: mainRoot
    title: Qt.application.name
    width: 800
    height: 600
    visible: true
    menuBar: MainMenu { id: mainMenu }
    statusBar: StatusBar {
        Label {
            text: isConnected ? qsTr("Connected to " + webSocket.url) : qsTr("Disconnected")
        }
    }

    Component.onCompleted: {
        var geometry = Settings.map("MainWindow")
        if (Object.keys(geometry).length) {
            x = geometry.x
            y = geometry.y
            width = geometry.width
            height = geometry.height
        } else {
            if (Screen.width && Screen.height) {
                x = (Screen.width - width) / 2
                y = (Screen.height - height) / 2
            } else {
                x = 200
                y = 200
            }
        }
        webSocket.active = Settings.value("Common", "autoconnect") === "true"
        infuTableContainer.visible = Settings.value("InfuTable", "visible", true) === "true"
    }

    function createObjInMainContext(url, properties) {
        Utils.createDynamicObject(mainRoot, url, properties ? properties : {})
    }

    onClosing: {
        Settings.setMap("MainWindow", {
            x: x,
            y: y,
            width: width,
            height: height
        })
        Settings.setValue("InfuTable", "visible", infuTableContainer.visible)
    }

    Net {
        id: net
    }

    WebSocket {
        id: webSocket
        url: String("ws://%1:%2").arg(Settings.value("Infusoria", "address")).arg(Settings.value("Infusoria", "port"))

        onStatusChanged: {
            if (status === WebSocket.Open) {
                InfuProto.getInfusories()
            }
        }

        onTextMessageReceived: InfuProto.receive(message)
    }

    QtObject {
        id: infuManager
        signal log(var line)
        signal infusoriaInfo(var info)
    }

    ListModel {
        id: infuModel
    }

    SplitView {
        anchors.fill: parent

        TabView {
            id: tabView
            Layout.fillWidth: true
            Layout.margins: 7

            function openInfusoria() {
                var name = infuModel.get(infuTableView.currentRow).name
                for (var i = 0; i < count; i++) {
                    if (getTab(i).item.name === name) {
                        currentIndex = i
                        return
                    }
                }

                var tab = addTab(name)
                var uuid = infuModel.get(infuTableView.currentRow).uuid
                tab.setSource("qrc:/qml/main/WorkArea.qml", { name: name, uuid: uuid })
                currentIndex = tabView.count - 1
            }
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

                onDoubleClicked: tabView.openInfusoria()

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
                    text: qsTr("Open")
                    enabled: infuTableView.currentRow >= 0
                    onClicked: tabView.openInfusoria()
                }

                Button {
                    Layout.fillWidth: true
                    text: qsTr("Close")
                    enabled: infuTableView.currentRow >= 0
                    onClicked: {
                        var name = infuModel.get(infuTableView.currentRow).name
                        for (var i = 0; i < tabView.count; i++) {
                            if (tabView.getTab(i).item.name === name) {
                                tabView.removeTab(i)
                                return
                            }
                        }
                    }
                }
            }
        }
    }
}
