import QtQuick
import QtQuick.Controls
import "template/"
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
        model: ListModel {
            id: listSenderWidgets
        }
        delegate: Item {
            height: 100
            width: 250
            SenderWidget {
                onEventClickSend: {
                    coreTester.toSend(getId(), getPayload())
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        spacing: 5
        model: visualModel
    }
}
