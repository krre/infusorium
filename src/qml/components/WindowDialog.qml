import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2

Window {
    default property alias data: scrollView.data
    property alias scrollView: scrollView
    id: root
    width: 500
    height: 500
    minimumWidth: 200
    minimumHeight: 200
    visible: true
    modality: Qt.ApplicationModal

    signal accepted
    signal rejected

    onVisibleChanged: if (!visible) root.destroy()

    ColumnLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignHCenter
        spacing: 0

        ScrollView {
            id: scrollView
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            frameVisible: false
      }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Button {
                Layout.margins: 10
                Layout.rightMargin: 0
                text: qsTr("OK")
                onClicked: {
                    root.accepted()
                    root.destroy()
                }
            }

            Button {
                Layout.margins: 10
                Layout.leftMargin: 0
                text: qsTr("Cancel")
                onClicked: {
                    root.rejected()
                    root.destroy()
                }
            }
        }
    }
}
