import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "../components"
import "../../js/infu-proto.js" as InfuProto

WindowDialog {
    id: root
    title: qsTr("Logger")
    width: 900
    height: 500
    standardButtons: StandardButton.Close

    Component.onCompleted: InfuProto.getLog(true)
    Component.onDestruction: InfuProto.getLog(false)

    Connections {
        target: mainRoot.infuManager
        onLog: textArea.append(line)
    }

    TextArea {
        id: textArea
        anchors.fill: parent
        readOnly: true
    }
}
