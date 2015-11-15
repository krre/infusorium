import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import "main"

ApplicationWindow {
    id: mainRoot
    title: APP.name
    width: 800
    height: 600
    visible: true

    menuBar: MainMenu {}

    Component.onCompleted: {
        var geometry = SETTINGS.map("MainWindow")
        if (Object.keys(geometry).length) {
            x = geometry.x
            y = geometry.y
            width = geometry.width
            height = geometry.height
        } else {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        }
    }

    onClosing: {
        SETTINGS.setMap("MainWindow", {
            x: x,
            y: y,
            width: width,
            height: height
        })
    }

    TabView {
        id: tabView
        anchors.fill: parent
        frameVisible: false
    }
}
