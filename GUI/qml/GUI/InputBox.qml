import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

Rectangle{
    id:backGround
    width: 100
    height: boxLabel.height + box.height + 5
    border.width: 0
    property alias label: boxLabel.text
    property alias value: boxInput.text
    property alias validator: boxInput.validator
    property alias mask: boxInput.inputMask
    property alias active: boxInput.focus
    property alias inputMethodHints: boxInput.inputMethodHints
    color: "#E7E6FA"
    signal acepted();
    function setInput( inputText){
        boxInput.text = inputText
    }
    onActiveFocusChanged: {
        if(focus){
            boxInput.forceActiveFocus();
            boxInput.cursorPosition=0
            boxInput.selectAll();
        }
    }
    Column{
        id: container
        anchors.fill: parent

        Text {
            id: boxLabel
            text: label
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

                onAccepted: acepted()
                onFocusChanged: {
                    if(activeFocus){
                        boxInput.cursorPosition=0
                        boxInput.selectAll();
                    }
                }

            }
        }
    }
}
