import QtQuick 2.5
import QtQuick.Controls 1.4
import Aquarium 1.0

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath

    Component.onCompleted: {
        process.run(SETTINGS.value("Infusoria", "executable"), [filePath])
    }

    Component.onDestruction: process.shutdown()

    Process {
        id: process
    }
}
