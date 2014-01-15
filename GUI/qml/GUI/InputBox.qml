import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

Rectangle{
    id:backGround
    width: parent.width
    height: boxLabel.height + box.height + 5
    border.width: 0
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#faf0f0"
        }

        GradientStop {
            position: 1
            color: "#96d4c5"
        }
    }
    property alias label: boxLabel.text
    property alias value: boxInput.text
    property alias validator: boxInput.validator
    property alias mask: boxInput.inputMask
    property alias active: boxInput.focus

    signal acepted();
    function setInput( inputText){
        boxInput.text = inputText
    }
    onActiveFocusChanged: {
        if(focus){
            boxInput.forceActiveFocus();
        }
    }
    Column{
        id: container
        anchors.fill: parent

        Label {
            id: boxLabel
            text: label
            width: parent.width
        }
        Rectangle{
            id: box
            width: parent.width
            height: boxInput.height + 5
            radius: 4
            //            border.color: "black"
            //            border.width: 0

            TextInput{
                id: boxInput
                anchors.centerIn: parent
                width: parent.width-5
                color: "#000000"
                onAccepted: acepted()
            }
        }
    }
}
