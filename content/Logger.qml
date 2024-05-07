import QtQuick

Rectangle {
    color: "cyan"
    border.color: "black"
    border.width: 1

    function addRecord(record) {
        log.text += '\n' + record
    }

    TextEdit {
        id: log
        anchors.fill: parent
        anchors.margins: 8
        wrapMode: TextEdit.Wrap
    }
}
