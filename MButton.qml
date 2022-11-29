import QtQuick 2.7
import QtQuick.Controls 2.3

Button {
    id: _btn

    property color clr: clr_exit
    property color clr_enter: "#008B8B"
    property color clr_exit: "#000000"
    property color clr_click: "#2F4F4F"

    contentItem: Label {
        text: _btn.text
        font: _btn.font
        color: clr
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: clr

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 1
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        hoverEnabled: true

        onPressed: {
            clr = clr_click
            mouse.accepted = false;
        }
        onEntered: {
            clr = clr_enter
        }
        onExited: {
            clr = clr_exit
        }
    }
}
