import QtQuick 2.0
import QtQuick 2.0

Item {
    id : container
    property string messageText: "text"
    function show(){
        width = parent.width
        height = parent.height
        rootLoader.sourceComponent = messageBody
    }
    function hide(){
        width = 0
        height = 0
        rootLoader.sourceComponent = nullCompenet
    }
    Loader{
        id: rootLoader
        anchors.fill : parent
    }
    Component{
        id: nullCompenet
        Item {
        }
    }
    Component {
        id: messageBody
        Rectangle{
            color: "#50424242"
            anchors.fill: parent
            Column{
                id: dialogBox
                width: 200
                height: 100
                anchors.centerIn: parent
                Text {
                    id: message
                    text: messageText
                }
                SimpleButton{
                    text: qsTr("Aceptar")
                    onClicked: hide()
                }
            }
        }
    }

}


