import QtQuick
import QtQuick.Controls

Rectangle{
    id: root
    width: 100
    height: 24
    property int _margin: 5
    property string _text
    property variant _validator



    color: "lightgrey"
    border.color: "black"
    border.width: 1
    clip: true
    radius: 5
    TextInput {
        id: inputText
        anchors.fill: parent
        anchors.margins: _margin
        text: root._text
        validator: _validator ? _validator : IntValidator

        onTextChanged: {
            root._text = text
        }
    }

    function getText(){
        return inputText.text
    }
}
