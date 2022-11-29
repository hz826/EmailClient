import QtQuick 2.7
import QtQuick.Controls 2.3

Row {
    property alias hint : _text
    property alias input: _texf
    property alias text : _texf.text

    Text {
        anchors.verticalCenter: parent.verticalCenter
        renderType: Text.NativeRendering
        id: _text
    }

    TextField {
        anchors.verticalCenter: parent.verticalCenter
        width: input_width
        color: "black"
        id: _texf

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
