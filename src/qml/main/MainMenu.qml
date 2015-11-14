import QtQuick 2.5
import QtQuick.Controls 1.4

MenuBar {
    property alias recentUnitsModel: recentUnitsModel

    Menu {
        title: qsTr("Unit")

        MenuItem {
            text: qsTr("New...")
            shortcut: "Ctrl+N"
        }

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
        }

        Menu {
            id: recentUnitsMenu
            title: qsTr("Recent Units")
            enabled: recentUnitsModel.count > 0

            Instantiator {
                model: recentUnitsModel

                MenuItem {
                    text: model.filePath
                }

                onObjectAdded: recentUnitsMenu.insertItem(index, object)
                onObjectRemoved: recentUnitsMenu.removeItem(object)
            }

            MenuSeparator {
                visible: recentUnitsModel.count > 0
            }

            MenuItem {
                text: qsTr("Clear Menu")
                onTriggered: recentUnitsModel.clear()
            }

            ListModel {
                id: recentUnitsModel
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
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About Aquarium...")
        }
    }
}
