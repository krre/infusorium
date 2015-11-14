import QtQuick 2.5
import QtQuick.Dialogs 1.2

MessageDialog {
    title: qsTr(String("About %1").arg(APP.name))
    standardButtons: StandardButton.Ok
    text: String("<h3>%1 %2</h3>
          Build date: %3<br>
          Copyright (c) 2015, Vladimir Zarypov").arg(APP.name).arg(APP.version).arg(APP.buildDate)
    onVisibleChanged: if (!visible) destroy()
    Component.onCompleted: open()
}
