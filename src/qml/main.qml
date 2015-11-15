import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import "main"
import "../js/utils.js" as Utils
import "../js/settings.js" as Settings

ApplicationWindow {
    id: mainRoot
    title: APP.name
    width: 800
    height: 600
    visible: true

    menuBar: MainMenu {}

    Component.onCompleted: Settings.load()

    function createObjInMainContext(url, properties) {
        Utils.createDynamicObject(mainRoot, url, properties ? properties : {})
    }

    onClosing: {
        Settings.save()
    }

    TabView {
        id: tabView
        anchors.fill: parent
        frameVisible: false
    }
}
