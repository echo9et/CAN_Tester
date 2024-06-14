import QtQuick
import QtQuick.Controls

Item {
    id: root
    anchors.top: parent.top

    width: parent.width
    height: parent.height
    clip: true
    function addWidget() {
        listSenderWidgets.append({})
    }
    Rectangle {
        id: header
        height: 20
        width: 420
        color: "#af7ef5ff"
        Text {
            id: headerNum
            text: "#"
            width: 40
            anchors.left: parent.left
        }
        Text {
            id: headerTime
            text: "Time"
            width: 130
            anchors.left: headerNum.right
        }
        Text {
            id: headerID
            text: "Frame ID"
            width: 60
            anchors.left: headerTime.right
        }
        Text {
            id: headerDLC
            text: "DLC"
            width: 30
            anchors.left: headerID.right
        }
        Text {
            text: "Payload"
            width: 160
            anchors.left: headerDLC.right
        }
    }

    DelegateModel {
        id: visualModel
        model: dataMonitoring
        delegate: Item {
            height: 15
            width:  420
            property bool mode: isRX
            visible: mode && switchRX._text == "RX" ? switchRX._state
                                                    : switchTX._state
            Rectangle {
                height: 15
                width: 420
                color: count % 2 == 0 ? "lightgray" : "gray"
                Text {
                    id: label_id
                    text: count
                    width: 40
                    anchors.left: parent.left
                }
                Text {
                    id: label_time
                    text: time
                    width: 130
                    anchors.left: label_id.right
                }
                Text {
                    id: label_frame_id
                    text: id
                    width: 60
                    anchors.left: label_time.right
                }
                Text {
                    id: label_dlc
                    text: dlc
                    width: 30
                    anchors.left: label_frame_id.right
                }
                Text {
                    id: label_payload
                    text: payload
                    width: 160
                    anchors.left: label_dlc.right
                }
            }
        }
    }
    ScrollView {
        anchors.top: header.bottom
        width: parent.width
        height: parent.height - header.height
        spacing: 5

        Column {

            Repeater {
                model: visualModel
            }
        }
    }


}
