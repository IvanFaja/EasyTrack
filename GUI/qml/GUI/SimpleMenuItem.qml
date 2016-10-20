import QtQuick 2.0

Rectangle{
    id: root
    property alias text: label.text
    signal clicked()
    color: "white"
    width: parent.width
    height:  label.height
    MouseArea{
        anchors.fill: parent
        onClicked: menuDelegate.clicked()
    }


    Text {
        id: label
        text: ""
    }


}

