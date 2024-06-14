import QtQuick
import QtQuick.Controls
import "template/"
Grid {
    id: root
    height: 85
    width: 230
    anchors.fill: parent
    columns: 3
    rows: 3
    spacing: 5
    signal eventClickSend(string id, string payload, bool isRx)
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
        _validator: RegularExpressionValidator {
            regularExpression: /[0-9A-F]{8}/
        }
    }
    MyButton {
        id: cmdSend
        textButton: "Send"
        function click() {
            eventClickSend(inputID._text, inputPayload._text, true)
        }
    }

    // -------------- END -------------------

    // ------------ next row ----------------

    Text {
        text: "Payload:"
    }
    MyTextInput {
        id: inputPayload
        _text: "AABBCC"
        _validator: RegularExpressionValidator {
            regularExpression: /[0-9A-F]{16}/
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
        _validator: IntValidator{
            bottom: 10;
            top: 1000;
        }
    }

    Switch {
        Timer {
            id: timer
            interval: 1000; running: false; repeat: true
            onTriggered: cmdSend.click()
        }

        width: 70
        height: 20
        id: switchRun
        onClicked: {
            if ( checked ) {
                if ( inputTimer._text.length == 0 ) {
                    switchRun.checked = false
                    return;
                }
                timer.interval = inputTimer._text
                timer.running = true
            }
            else {
                timer.running = false
            }
        }
    }

}
