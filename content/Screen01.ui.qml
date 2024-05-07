

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import CANTester

Rectangle {
    id: rectangle
    width: 1080
    height: 540
    anchors.fill: parent

    color: Constants.backgroundColor

    Logger {
        id: logger
        width: parent.width - canWindow.width
        height: parent.height
        anchors.right: parent.right
    }

    CanWindow {
        id: canWindow
        width: 700
        height: parent.height
        anchors.left: parent.left
    }

    Connections {
        target: coreTester
        function onSendRecordLog(record) {
            logger.addRecord(record)
        }
    }
}
