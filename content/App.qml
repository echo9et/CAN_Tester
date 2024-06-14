// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import CANTester

Window {
    id: root
    width: 1920
    height: 1080
    minimumWidth: 1080
    minimumHeight: 540

    visible: true
    color: "lightgray"
    title: qsTr("Tester CAN")
    Screen01 {
        id: mainScreen
    }
}
