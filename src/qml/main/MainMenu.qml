import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog
import "../../js/files.js" as Files

MenuBar {

    Menu {
        title: qsTr("Infusoria")

        MenuItem {
            text: qsTr("Connect to IM...")
            enabled: !mainRoot.isConnected
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Connect.qml")
        }

        MenuItem {
            text: qsTr("Disconnect")
            enabled: mainRoot.isConnected
            onTriggered: {
                mainRoot.webSocket.active = false
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Close")
            shortcut: "Ctrl+W"
            onTriggered: tabView.removeTab(tabView.currentIndex)
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Close All")
            shortcut: "Ctrl+Shift+W"
            onTriggered: {
                while (tabView.count > 0) {
                    tabView.removeTab(0)
                }
            }
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Close Other")
            enabled: tabView.count > 1
            onTriggered: {
                var i = 0
                while (tabView.count > 1) {
                    if (i !== tabView.currentIndex) {
                        tabView.removeTab(i)
                    } else {
                        i++
                    }
                }
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            shortcut: "Ctrl+Q"
            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("Tools")

        MenuItem {
            text: qsTr("Options...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Options.qml")
        }
    }

    Menu {
        title: qsTr("Window")

        MenuItem {
            text: qsTr("Show Infusoria Table")
            checkable: true
            checked: infuTableContainer.visible
            onCheckedChanged: infuTableContainer.visible = checked
        }

        MenuItem {
            text: qsTr("Show Logger")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Logger.qml")
            enabled: mainRoot.isConnected
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr(String("About %1...").arg(Qt.application.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/About.qml")
        }
    }
}
