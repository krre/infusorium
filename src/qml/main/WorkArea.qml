import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtWebSockets 1.0
import Aquarium 1.0

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 7

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
