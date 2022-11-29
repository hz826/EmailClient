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

                MInput {
                    id: login_input1
                    input.objectName: "login_account"
                    hint.width: text_width
                    input.width: input_width

                    hint.text: "账号:"

//                    input.KeyNavigation.tab: login_input2
                    input.onEditingFinished: listener.update_username()
                    input.focus: true
                }

                MInput {
                    id: login_input2
                    input.objectName: "login_password"
                    hint.width: text_width
                    input.width: input_width

                    hint.text: "密码:"

//                    KeyNavigation.tab: login_botton
                    input.echoMode: TextInput.Password
                    input.passwordCharacter: "*"
                    input.passwordMaskDelay: 1500
                }

                MInput {
                    id: login_input3
                    input.objectName: "smtp_server"
                    hint.width: text_width
                    input.width: input_width

                    hint.text: "SMTP服务器:"
                }

                MInput {
                    id: login_input4
                    input.objectName: "pop3_server"
                    hint.width: text_width
                    input.width: input_width

                    hint.text: "POP3服务器:"
                }
            }

            MButton {
                anchors.verticalCenter: parent.verticalCenter
                KeyNavigation.tab: login_input1
                id: login_botton
                text: "登录"
                onClicked: listener.login()
                Keys.onEnterPressed: listener.login()
            }
        }
    }
}
