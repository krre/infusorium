import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Window {
    id: root
    width: 500
    height: 500
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    color: sysPalette.window

    onVisibleChanged: if (!visible) root.destroy()

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 7

        TextArea {
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
