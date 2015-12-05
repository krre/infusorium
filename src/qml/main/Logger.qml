import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import "../../js/infu-proto.js" as InfuProto

Window {
    id: root
    title: qsTr("Logger")
    width: 900
    height: 500
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    color: sysPalette.window

    onVisibleChanged: if (!visible) root.destroy()

    Component.onCompleted: InfuProto.getLog(true)
    Component.onDestruction: InfuProto.getLog(false)

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    Connections {
        target: mainRoot.infuManager
        onLog: textArea.append(line)
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 7

        TextArea {
            id: textArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Close")
            onClicked: root.destroy()
        }
    }
}
