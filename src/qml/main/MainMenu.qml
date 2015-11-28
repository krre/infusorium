import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog
import "../../js/files.js" as Files

MenuBar {
    property alias recentFilesModel: recentFilesModel

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: {
                var fileDialog = Dialog.selectFile(mainRoot, { nameFilters: [ qsTr("Infusoria Files (*.infu)"), qsTr("All files (*)") ],
                    folder: UTILS.pathToUrl(SETTINGS.value("Infusoria", "workspace", UTILS.homePath))})
                fileDialog.accepted.connect(function() {
                    Files.openFile(UTILS.urlToPath(fileDialog.fileUrl))
                })
            }
        }

        Menu {
            id: recentFilesMenu
            title: qsTr("Recent Files")
            enabled: recentFilesModel.count > 0

            Instantiator {
                model: recentFilesModel

                MenuItem {
                    text: model.filePath
                    onTriggered: Files.openFile(text)
                }

                onObjectAdded: recentFilesMenu.insertItem(index, object)
                onObjectRemoved: recentFilesMenu.removeItem(object)
            }

            MenuSeparator {
                visible: recentFilesModel.count > 0
            }

            MenuItem {
                text: qsTr("Clear Menu")
                onTriggered: recentFilesModel.clear()
            }

            ListModel {
                id: recentFilesModel
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
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr(String("About %1...").arg(APP.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/About.qml")
        }
    }
}
