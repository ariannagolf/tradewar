import QtQuick 2.9
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 600
    height: 600
    Image {
        id: input
        source: "input.jpg"
        anchors.fill: parent

        OpacityMask {
            source: mask
            maskSource: input
        }

        LinearGradient {
            id: mask
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.2; color: "transparent"}
                GradientStop { position: 0.5; color: "white" }
            }
        }
    }
}
