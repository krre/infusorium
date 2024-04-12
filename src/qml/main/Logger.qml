import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs
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
