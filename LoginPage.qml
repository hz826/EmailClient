import QtQuick 2.7
import QtQuick.Controls 2.3

Rectangle {
    Rectangle {
        anchors.centerIn: parent
        radius: 10
        border.color: "black"
        width: 500
        height: 120

        Row {
            spacing: 50
            anchors.centerIn: parent
            id: login_row

            Column {
                spacing: 20

                Row {
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 90
                        renderType: Text.NativeRendering
                        text: "账号:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        text: ""
                        color: "black"
                        id: login_input1
                        focus: true
                        KeyNavigation.tab: login_input2

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
                        width: 90
                        renderType: Text.NativeRendering
                        text: "密码:"
                    }

                    TextField {
                        anchors.verticalCenter: parent.verticalCenter
                        width: 200
                        text: ""
                        color: "black"
                        id: login_input2
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
