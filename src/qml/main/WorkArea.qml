import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
}
