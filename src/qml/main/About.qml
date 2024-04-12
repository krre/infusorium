import QtQuick
import "../components/messagedialog"

MessageDialogBase {
    title: qsTr(String("About %1").arg(Qt.application.name))
    text: String("<h3>%1 %2</h3>
          Based on Qt %3<br>
          Build on %4<br><br>
          Copyright © 2015-2024, Vladimir Zarypov").arg(Qt.application.name).arg(APP.version).arg(APP.qtVersion).arg(APP.buildDate)
}
