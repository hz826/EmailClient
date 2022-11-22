import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    property int mode: 0
    anchors.fill: parent

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

            Button {
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

                background: Rectangle {
                    anchors.fill: parent
                    border.width: 1
                    border.color: "black"

                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 1
                    }
                }
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                text: "登出"
                onClicked: listener.exit()

                background: Rectangle {
                    anchors.fill: parent
                    border.width: 1
                    border.color: "black"

                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 1
                    }
                }
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


            Text {
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: 10
                width: parent.width - 20
                renderType: Text.NativeRendering
                wrapMode: Text.WordWrap
                text: "邮件内容加载中..."
                objectName: "read_text"

//                MouseArea {
//                    anchors.fill: parent
//                    drag.target: textEdit
//                    drag.axis: Drag.YAxis
//                    drag.minimumY: 480-parent.height
//                    drag.maximumY: 0
//                }

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

            Button {
                anchors.right: pageID.left
                anchors.verticalCenter: pageID.verticalCenter
                anchors.margins: 10
                text: "上一篇"
                onClicked: listener.getPrevious()

                background: Rectangle {
                    anchors.fill: parent
                    border.width: 1
                    border.color: "black"

                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 1
                    }
                }
            }

            Button {
                anchors.left: pageID.right
                anchors.verticalCenter: pageID.verticalCenter
                anchors.margins: 10
                text: "下一篇"
                onClicked: listener.getNext()

                background: Rectangle {
                    anchors.fill: parent
                    border.width: 1
                    border.color: "black"

                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 1
                    }
                }
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

                Row {
                    spacing: 10

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 90
                        renderType: Text.NativeRendering
                        text: "发送到:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 500
                        text: ""
                        color: "black"
                        objectName: "write_sendto"

                        background: Rectangle {
                            anchors.fill: parent
                            border.width: 1
                            border.color: "black"

                            Rectangle {
                                anchors.fill: parent
                                anchors.leftMargin: 0
                                anchors.topMargin: 0
                                anchors.rightMargin: 0
                                anchors.bottomMargin: 1
                            }
                        }
                    }
                }

                Row {
                    spacing: 10

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 90
                        renderType: Text.NativeRendering
                        text: "标  题:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 500
                        text: ""
                        color: "black"
                        objectName: "write_title"

                        background: Rectangle {
                            anchors.fill: parent
                            border.width: 1
                            border.color: "black"

                            Rectangle {
                                anchors.fill: parent
                                anchors.leftMargin: 0
                                anchors.topMargin: 0
                                anchors.rightMargin: 0
                                anchors.bottomMargin: 1
                            }
                        }
                    }
                }
            }

            Button {
                anchors.right: parent.right
                anchors.verticalCenter: rect_write_to.verticalCenter
                anchors.verticalCenterOffset: 10
                anchors.margins: 10
                text: "发送"
                onClicked: listener.send()

                background: Rectangle {
                    anchors.fill: parent
                    border.width: 1
                    border.color: "black"

                    Rectangle {
                        anchors.fill: parent
                        anchors.leftMargin: 0
                        anchors.topMargin: 0
                        anchors.rightMargin: 0
                        anchors.bottomMargin: 1
                    }
                }
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
