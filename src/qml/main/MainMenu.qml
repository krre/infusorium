import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog
import "../../js/files.js" as Files

MenuBar {
    property alias recentUnitsModel: recentUnitsModel

    Menu {
        title: qsTr("Unit")

        MenuItem {
            text: qsTr("New...")
            shortcut: "Ctrl+N"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/unit/NewUnit.qml")
        }

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: {
                var fileDialog = Dialog.selectFile(mainRoot, { nameFilters: [ qsTr("Infusoria Files (*.infu)"), qsTr("All files (*)") ],
                    folder: UTILS.pathToUrl(SETTINGS.value("Infusoria", "workspace", UTILS.homePath))})
                fileDialog.accepted.connect(function() {
                    Files.openUnit(UTILS.urlToPath(fileDialog.fileUrl))
                })
            }
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
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Options.qml")
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr(String("About %1...").arg(APP.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/About.qml")
        }
    }
}
