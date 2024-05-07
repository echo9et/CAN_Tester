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
    DelegateModel {
        id: visualModel
        model: dataMonitoring
        delegate: Item {
            height: 15
            width:  420
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

    ListView {
        anchors.fill: parent
        spacing: 5
        model: visualModel
        header: headerComponent
    }

    Component {
        id: headerComponent
        Rectangle {
            height: 20
            width: 420
            color: "blue"
            Text {
                id: label_id
                text: "#"
                width: 40
                anchors.left: parent.left
            }
            Text {
                id: label_time
                text: "Time"
                width: 130
                anchors.left: label_id.right
            }
            Text {
                id: label_frame_id
                text: "Frame ID"
                width: 60
                anchors.left: label_time.right
            }
            Text {
                id: label_dlc
                text: "DLC"
                width: 30
                anchors.left: label_frame_id.right
            }
            Text {
                id: label_payload
                text: "Payload"
                width: 160
                anchors.left: label_dlc.right
            }
        }
    }
}
