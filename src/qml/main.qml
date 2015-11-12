import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import Osg 1.0 as Osg

ApplicationWindow {
    id: mainRoot
    title: "Aquarium"
    width: 800
    height: 600
    visible: true

    Osg.Viewer {
        anchors.fill: parent
        camera {
            clearColor: "gray"
            fovy: 30
            aspectRatio: width / height
            zNear: 0.1
            zFar: 10000
        }

        sceneData: Osg.Geode {

            Osg.ShapeDrawable {
                color: "red"
                shape: Osg.Box {
                    halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
                }
            }
        }
    }
}
