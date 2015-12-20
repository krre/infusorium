import QtQuick 2.5
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr("About Aquarium")
    standardButtons: StandardButton.Ok
    text: String("<h3>Aquarium %1</h3>
          Based on Qt %2<br>
          Build on %3<br><br>
          Copyright (c) 2015, Vladimir Zarypov").arg(APP.version).arg(APP.qtVersion).arg(APP.buildDate)
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
