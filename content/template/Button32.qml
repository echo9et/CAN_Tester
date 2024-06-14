import QtQuick
import QtQuick.Controls

Button{
    id: button
    property int _size: 32
    property string _path_icon: "./images/plus_" + _size + ".png"
    width: _size
    height: _size
    icon.source: _path_icon
    icon.height: _size
    icon.width: _size
    icon.color: button.down ? "#dd7ff7f4" :  "#FF000000"
    background: Rectangle {
        color: button.down ? "#dbE7FAFC" : "#00ffffff"
        border.width: 0
        radius: _size / 2
    }
}
