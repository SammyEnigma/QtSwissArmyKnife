﻿import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

HelpPagePanel {
    id: root

    property var images: [
        "qrc:/resources/images/QSAKQQ.jpg",
        "qrc:/resources/images/QtQQ.jpg"
    ]

    RowLayout {
        width: root.width - root.leftPadding - root.rightPadding
        Repeater {
            model: images
            Image {
                source: modelData
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.maximumHeight: 350
            }
        }
    }
}
