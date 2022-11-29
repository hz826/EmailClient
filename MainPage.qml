import QtQuick 2.7
import QtQuick.Controls 2.3

Rectangle {
    property int mode: 0
    anchors.fill: parent

    MouseArea{
        anchors.fill: parent
        onWheel: {
            if (vbar.size < 1) {
                if (wheel.angleDelta.y > 0) {
                    vbar.decrease();
                } else {
                    vbar.increase();
                }
            }
//            console.log(vbar.position)
//            console.log(frame.height, content.height)
        }
    }

    Rectangle {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        width: parent.width - 20
        height: 120
        id: info_box

        radius: 10
        border.color: "black"

        Text {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10
            width: 90
            renderType: Text.NativeRendering
            text: "欢迎"
            objectName: "read_info"
        }

        Row {
            anchors.right: parent.right
            height: parent.height
            anchors.margins: 10
            spacing: 10

            MButton {
                anchors.verticalCenter: parent.verticalCenter
                text: "写信"
                id: switch_mode

                onClicked: {
                    if (mode == 0) {
                        rect_read.visible = false
                        rect_write.visible = true
                        switch_mode.text = "读信"
                        mode = 1
                    } else {
                        rect_read.visible = true
                        rect_write.visible = false
                        switch_mode.text = "写信"
                        mode = 0
                    }
                }
            }

            MButton {
                anchors.verticalCenter: parent.verticalCenter
                text: "登出"
                onClicked: listener.exit()
            }
        }
    }

    Rectangle {
        anchors.top: info_box.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            width: parent.width - 20
            id: rect_read
            radius: 10
            border.color: "black"

            Rectangle {
                anchors.top: parent.top
                anchors.bottom: pageID.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 10
                width: parent.width - 20
                clip: true
                id: frame

                Text {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: -vbar.position * height

                    renderType: Text.NativeRendering
                    wrapMode: Text.WordWrap
                    text: "邮件内容加载中..."
                    objectName: "read_text"
                    id: content
                    focus: true
                }

                ScrollBar {
                    id: vbar
                    hoverEnabled: true
                    orientation: Qt.Vertical
                    size: frame.height / content.height
                    active: true
                    width: 10
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    objectName: "read_vbar"
                }
            }

            Text {
                id: pageID
                anchors.bottom: parent.bottom
                anchors.margins: 20
                anchors.horizontalCenter: parent.horizontalCenter
                renderType: Text.NativeRendering
                text: "第0/0篇"
                objectName: "read_pageid"
            }

            MButton {
                anchors.right: pageID.left
                anchors.verticalCenter: pageID.verticalCenter
                anchors.margins: 10
                text: "上一篇"
                onClicked: listener.getPrevious()
            }

            MButton {
                id: next_page
                anchors.left: pageID.right
                anchors.verticalCenter: pageID.verticalCenter
                anchors.margins: 10
                text: "下一篇"
                onClicked: listener.getNext()
            }

            MButton {
                anchors.left: next_page.right
                anchors.verticalCenter: pageID.verticalCenter
                anchors.margins: 10
                text: "删除"
                onClicked: listener.del()
            }
        }

        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10

            width: parent.width - 20
            id: rect_write
            visible: false

            radius: 10
            border.color: "black"

            Column {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 10
                spacing: 20
                height: 60
                id: rect_write_to

                MInput {
                    hint.width: 90
                    input.width: 500
                    hint.text: "发送到:"
                    objectName: "write_sendto"
                }

                MInput {
                    hint.width: 90
                    input.width: 500
                    hint.text: "标  题:"
                    objectName: "write_title"
                }
            }

            MButton {
                anchors.right: parent.right
                anchors.verticalCenter: rect_write_to.verticalCenter
                anchors.verticalCenterOffset: 10
                anchors.margins: 10
                text: "发送"
                onClicked: listener.send()
            }

            Text {
                anchors.top: rect_write_to.bottom
                anchors.topMargin: 80
                anchors.left: parent.left
                anchors.margins: 10

                width: 90
                renderType: Text.NativeRendering
                text: "正  文:"
                id: rect_main
            }

            TextEdit {
                anchors.top: rect_write_to.bottom
                anchors.topMargin: 80
                anchors.bottom: parent.bottom
                anchors.left: rect_main.right
                anchors.right: parent.right
                anchors.margins: 20
                width: parent.width - 20
                objectName: "write_body"

                color: "black"
                text: ""
                selectByMouse: true
                renderType: Text.NativeRendering
                wrapMode: TextEdit.Wrap
            }
        }
    }
}
