import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    signal eventCmdConnect()
    property string textButton: "Push me"
    property int iWidth: 70
    property int iHeight: 20
    function click() {}
    border.width: 1
    border.color: "darkgray"
    color: mouseArea.pressed ? "gray" : "lightgray"
    width: iWidth
    height: iHeight
    radius: 5
    clip: true

    Text {
        anchors.centerIn: parent
        text: root.textButton
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onReleased: {
            root.click()
        }
    }
}
