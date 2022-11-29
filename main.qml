import QtQuick 2.7
import QtQuick.Window 2.2
import myEmailClient 1.0

Window {
    visible: true
    width: 1000
    height: 1000
    title: qsTr("myEmailClient")

    property bool isFirst : true;

    Listener {
        id: listener
        objectName: "listener"
    }

    LoginPage {
        objectName: "loginpage"
        anchors.fill: parent
        visible: true
    }

    MainPage {
        objectName: "mainpage"
        anchors.fill: parent
        visible: false
    }
}
