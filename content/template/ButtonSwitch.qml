import QtQuick
import QtQuick.Controls

Button {
    id: root
    property bool _state: true
    property string _text: "FF"
    function click() {}
    width: 32
    height: 32
    Text {
        id: filtrRx
        color: root._state ? "#00b110" : "#000000"
        text: qsTr(_text)
        font.pointSize: 12
        font.bold: true
        anchors.centerIn: parent
    }

    onClicked: {
        _state = !_state
        click()
    }

}
