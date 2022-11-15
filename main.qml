import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import Tooska 1.0
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 1000
    height: 1000
    title: qsTr("myEmailClient")

    property bool isFirst : true;

    Listener {
        id: listener
        objectName: "m_listener"
    }

    Loader {
        id: loader
        objectName: "m_loader"
        anchors.fill: parent // 弹出的界面都居中显示
        source: "LoginPage.qml" // 一开始显示登录页面
    }
}
