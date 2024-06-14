import QtQuick
import QtQuick.Controls
Rectangle {
    color: "cyan"
    border.color: "black"
    border.width: 1

    function addRecord(record) {
        log.text += record + '\n'
    }
    ScrollView {
        id: view
        anchors.fill: parent
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        TextEdit {
            id: log
            anchors.fill: parent
            anchors.margins: 8
            wrapMode: TextEdit.Wrap
            layer.enabled: false
        }
    }

}
