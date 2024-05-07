import QtQuick
import QtQuick.Controls

Grid {
    id: root
    height: 85
    width: 230
    anchors.fill: parent
    columns: 3
    rows: 3
    spacing: 5
    signal eventClickSend(string id, string payload)

    function getId() {
        return inputID.getText();
    }

    function getPayload() {
        return inputPayload.getText();
    }

    // -------------- END -------------------

    // ------------ next row ----------------

    Text {
        text: "ID:"
    }
    MyTextInput {
        id: inputID
        _text: "AAA"
    }
    MyButton {
        id: cmdSend
        textButton: "Send"
        function click() {
            eventClickSend(inputID._text, inputPayload._text)
        }
    }

    // -------------- END -------------------

    // ------------ next row ----------------

    Text {
        text: "Payload:"
    }
    MyTextInput {
        _text: "AA BB CC DD"
        id: inputPayload

        on_TextChanged: {
            _payload = text
        }
    }
    Text {
        width: 70
        height: 20        
        text: "Action:"
        horizontalAlignment: Text.AlignHCenter
    }

    // -------------- END -------------------

    // ------------ next row ----------------

    Text {
        text: "Timer:"
    }
    MyTextInput {
        id: inputTimer
    }

    Switch {
        width: 70
        height: 20
        id: switch1
    }

}
