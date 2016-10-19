import QtQuick 2.0

Rectangle {
    id: container
    width: label.width + 3
    height: label.height + 3
    signal clicked()
    property alias text: label.text
    border.color: "grey"
    Text {
        anchors.centerIn: parent
        id: label
        text: "button"
    }
    MouseArea{
      anchors.fill: parent
      onClicked: container.clicked()
    }
}
