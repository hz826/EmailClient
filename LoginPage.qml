import QtQuick 2.7
import QtQuick.Controls 2.3

Rectangle {
    property int text_width: 170
    property int input_width: 350

    Rectangle {
        anchors.centerIn: parent
        radius: 10
        border.color: "black"
        width: 700
        height: 300

        Row {
            spacing: 50
            anchors.centerIn: parent
            id: login_row

            Column {
                spacing: 20

                Row {
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: text_width
                        renderType: Text.NativeRendering
                        text: "账号:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: input_width
                        text: ""
                        color: "black"
                        id: login_input1
                        objectName: "login_account"
                        focus: true
                        KeyNavigation.tab: login_input2
                        onEditingFinished: listener.update_username()

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
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: text_width
                        renderType: Text.NativeRendering
                        text: "密码:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: input_width
                        text: ""
                        color: "black"
                        id: login_input2
                        objectName: "login_password"
                        KeyNavigation.tab: login_botton
                        echoMode: TextInput.Password
                        passwordCharacter: "*"
                        passwordMaskDelay: 1500

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
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: text_width
                        renderType: Text.NativeRendering
                        text: "SMTP服务器:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: input_width
                        text: ""
                        color: "black"
                        id: login_input3
                        objectName: "smtp_server"

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
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: text_width
                        renderType: Text.NativeRendering
                        text: "POP3服务器:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: input_width
                        text: ""
                        color: "black"
                        id: login_input4
                        objectName: "pop3_server"

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
                anchors.verticalCenter: parent.verticalCenter
                text: "登录"
                id: login_botton
                onClicked: listener.login()
                Keys.onEnterPressed: listener.login()
                KeyNavigation.tab: login_input1

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
}
