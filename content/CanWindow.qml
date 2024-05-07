import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 700
    height: 800
    color: "#efefef"
    border.color: "black"
    border.width: 1
    property string currentInterface
    signal eventClickConnect(string name_interface, string bitrate)
    signal eventClickDisconnect(string name_interface)

    Item {
        id: settingsConnect
        width: parent.width / 2 - 30
        property int iMargins: 10
        property int iHeightElement: 40
        height: 110

        anchors {
            top: parent.top
            left: parent.left
            margins: settingsConnect.iMargins
        }

        Rectangle {
            color: "#ececec"
            border.color: "#93000000"
            anchors.fill: parent
            border.width: 1
            radius: 25

        }

        ComboBox {
            id: comboBoxIntefaces
            model: coreTester.interfaces
            width: parent.width / 2 - 2 * settingsConnect.iMargins
            height: settingsConnect.iHeightElement
            anchors {
                top : parent.top
                left: parent.left
                margins: settingsConnect.iMargins
            }
            onCurrentTextChanged: {
                currentInterface = comboBoxIntefaces.currentText
            }
        }

        MyButton {
            id: cmdConnect
            iWidth: parent.width / 4 - settingsConnect.iMargins
            anchors.top : comboBoxIntefaces.top
            anchors.left: comboBoxIntefaces.right
            height: comboBoxIntefaces.height
            anchors.leftMargin: settingsConnect.iMargins
            textButton: "Connect"
            function click() {
                eventClickConnect(root.currentInterface, comboBoxBitrate.currentText)
            }
        }

        MyButton {
            id: cmdDisconnect
            iWidth: parent.width / 4 - settingsConnect.iMargins
            anchors.top : cmdConnect.top
            anchors.left: cmdConnect.right
            height: cmdConnect.height
            anchors.leftMargin: settingsConnect.iMargins
            textButton: "Disconnect"
            function click() {
                root.eventClickDisconnect(root.currentInterface)
            }
        }

        Text {
            text: "битрейт:"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            height: settingsConnect.iHeightElement
            anchors {
                right : comboBoxBitrate.left
                top : cmdConnect.bottom
                margins: settingsConnect.iMargins
            }
        }

        ComboBox {
            id: comboBoxBitrate
            model: ["10000", "20000", "50000", "100000", "250000", "500000" ]
            currentIndex: 4
            anchors {
                top : cmdConnect.bottom
                left: comboBoxIntefaces.right
                margins: settingsConnect.iMargins
            }
            height: settingsConnect.iHeightElement
            width: cmdConnect.width + cmdDisconnect.width + settingsConnect.iMargins
            onCurrentTextChanged: {
                currentInterface = comboBoxIntefaces.currentText
            }
        }
    }

    Item {
        id: screenComands

        height: settingsConnect.height
        width:  settingsConnect.width
        Rectangle {
            color: "#ececec"
            border.color: "#93000000"
            anchors.fill: parent
            border.width: 1
            radius: 25
        }

        anchors { top: parent.top; right: parent.right }
        anchors.margins: 10
        MyButton {
            id: addWidgetSender
            width: 140
            textButton: "Add \"Sender Widget\""
            function click() {
                areaSenderWidgets.addWidget()
            }
        }

        anchors {
            top: parent.top
            left: settingsConnect.right
        }
    }

// --------------------------     END   ----------------------------------

// ----------------------    SenderWidgets   ------------------------------

    GroupBox {
        id: groupBoxSenderWidgets;
        title: "Виджеты отправки"
        anchors.top: settingsConnect.bottom
        anchors.left: root.left
        anchors.margins: 10
        width: 250
        height: parent.height - settingsConnect.height - 30
        spacing: 3
        AreaSenderWidgets {
            id: areaSenderWidgets
        }
    }

    GroupBox {
        title: "Monitoring"
        anchors.top: settingsConnect.bottom
        anchors.left: groupBoxSenderWidgets.right
        width: root.width -  groupBoxSenderWidgets.width - 30
        height: parent.height - settingsConnect.height - 30
        anchors.margins: 10
        spacing: 3
        AreaMonitoring {
        }
    }

    Component.onCompleted: {
        root.eventClickConnect.connect(coreTester.toConnect)
        root.eventClickDisconnect.connect(coreTester.toDisconnect)
    }

}
