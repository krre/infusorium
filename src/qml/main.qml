import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2
import QtWebSockets 1.0
import Aquarium 1.0
import "main"
import "../js/utils.js" as Utils
import "../js/settings.js" as Settings
import "../js/infu-proto.js" as InfuProto

ApplicationWindow {
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias webSocket: webSocket
    property alias infuManager: infuManager
    property bool isConnected: webSocket.status === WebSocket.Open
    id: mainRoot
    title: "Aquarium"
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
        Settings.load()
        if (SETTINGS.value("Common", "autoconnect") === "true") {
            webSocket.active = true
        }
    }

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
