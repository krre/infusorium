import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import "../components"

WindowDialog {
    property string unitPath
    title: qsTr("Infusoria Console")
    width: 600
    height: 400
    standardButtons: StandardButton.Close

    Component.onCompleted: textArea.text = unitPath

    TextArea {
        id: textArea
        anchors.fill: parent
    }
}

