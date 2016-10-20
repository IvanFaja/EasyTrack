import QtQuick 2.0

Item {
    id : container
    MouseArea{
        anchors.fill: parent
    }
    property string messageText: "text"
    //    width: screenWidth
    //    height: screenWidth

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
            id: messageContainer
            color: "#E7E6FA"
            anchors.fill: parent
            property real dimm: 0.8
            property int animationDuration: 250
            property bool platformInverted: false
            property bool open: false
            state: "Hidden"
            Component.onCompleted: {
                messageContainer.state ="Visible"
                open = true;
            }
            states: [
                  State {
                      name: "Visible"
                      PropertyChanges { target: messageContainer; opacity: dimm }
                  },
                  State {
                      name: "Hidden"
                      PropertyChanges { target: messageContainer; opacity: 0.0 }
                  }
              ]

              transitions: [
                  Transition {
                      from: "Hidden"; to: "Visible"
                      NumberAnimation { properties: "opacity"; duration: animationDuration; easing.type: Easing.Linear }
                  },
                  Transition {
                      from: "Visible"; to: "Hidden"
                      NumberAnimation { properties: "opacity"; duration: animationDuration; easing.type: Easing.Linear }

                  }
              ]
              onStateChanged: {
                  if (state == "Hidden" && open ){
                      hide()
                  }

              }
            Flickable{
                anchors.fill: parent
                contentHeight: dialogBox.height
                contentWidth: dialogBox.width
                leftMargin: width/2 - dialogBox.width/2
                topMargin:  height/2 - dialogBox.height/2
                Rectangle{
                id: dialogBox
                width: 200
                height: 100
                color: "#E7E6FA"
                anchors.centerIn: parent
                Text {
                    id: label
                    text: messageText
                    width: parent.width -10
                    wrapMode:Text.WordWrap
                    anchors { horizontalCenter:  parent.horizontalCenter; top: parent.top; margins:  10 }
                }

                SimpleButton{
                    width: parent.width
                    height: 40
                    anchors { horizontalCenter:  parent.horizontalCenter; bottom:  parent.bottom ; }
                    text: qsTr("Aceptar")
                    onClicked: {

                       messageContainer.state = "Hidden"
//                        messageBody.destroy()
                    }
                }
            }
        }

}
    }

}
