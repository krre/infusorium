import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import "main"

ApplicationWindow {
    id: mainRoot
    title: "Aquarium"
    width: 800
    height: 600
    visible: true

    menuBar: MainMenu {}

    TabView {
        id: tabView
        anchors.fill: parent
        frameVisible: false
    }
}
