import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtWebSockets 1.0
import Aquarium 1.0
import "../../js/infu-proto.js" as InfuProto

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string name
    property string uuid

    Component.onCompleted: InfuProto.getInfusoria(uuid)

    Connections {
        target: mainRoot.infuManager
        onInfusoriaInfo: {
            print(info.uuid, uuid)
            if (info.uuid !== uuid) return
            infoLabel.text = "<b>" + qsTr("Base") + "</b><br><br>" +
                    qsTr("Name:") + "\t" + info.name + "<br>" +
                    qsTr("Uuid:") + "\t" + uuid + "<br>" +
                    qsTr("Birthday:") + "\t" + new Date(Number(info.birthday)).toLocaleString() + "<br><br>" +
                    "<b>" + qsTr("Individuality") + "</b><br><br>" +
                    qsTr("Sociability:") + "\t" + Number(info.individuality.sociability).toFixed(4) + " - " +
                    (Number(info.individuality.sociability) < 0 ? qsTr("Silent") : qsTr("Talkative")) + "<br>" +
                    qsTr("Zeal:") + "\t" + Number(info.individuality.zeal).toFixed(4) + " - " +
                    (Number(info.individuality.zeal) < 0 ? qsTr("Lazy") : qsTr("Hardworking")) + "<br>" +
                    qsTr("Activity:") + "\t" + Number(info.individuality.activity).toFixed(4) + " - " +
                    (Number(info.individuality.activity) < 0 ? qsTr("Thinker") : qsTr("Working")) + "<br>"
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 7

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label {
                id: infoLabel
            }
        }
    }
}
