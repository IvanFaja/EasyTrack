import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Styles 1.1
import "qrc:/qml/GUI"

ApplicationWindow {
    title: "Stocks"
    id: mainWindow
    width: 320
    height: 480
    visible: true
    menuBar: MenuBar{
        Menu{
            title: qsTr("Alamcenamiento")
            MenuItem {
                  text: qsTr("Copia de seguridad")
                  onTriggered:itemManager.backup()
              }
            MenuItem {
                  text: qsTr("Restaurar")
                  onTriggered:itemManager.restore()
              }
        }
    }

    statusBar: StatusBar{
        RowLayout {
                   Label { text: "Icons by: FastIcon.com"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: itemManager.openUrl("http://www.fasticon.com")
                    }
                   }
               }
    }

    Component.onCompleted: {
        itemManager.done.connect(workDone)
    }
    function workDone( succeed){
        if(succeed){
            messageDialog.title = qsTr("Ok")
        }else{
            messageDialog.title = qsTr("Cuidado")
        }
        messageDialog.text = itemManager.messageText
        messageDialog.informativeText = itemManager.detailedInfo
        messageDialog.open()
    }
    MessageDialog{
        id: messageDialog

    }

    TabView{
        id: tabs
        anchors.fill: parent
        style: TabViewStyle {
                    frameOverlap: 1
                    tab: Rectangle {
                        color: styleData.selected ? "#E7E6FA" :"silver"
                        border.color:  "white"
                        implicitWidth: Math.max(text.width + 4, 80)
                        implicitHeight: 30
                        radius: 3
                        Text {
                            id: text
                            anchors.margins: 2
                            anchors.centerIn: parent
                            text: styleData.title
                            color: styleData.selected ? "black" : "black"
                        }
                    }
                    frame: Rectangle {
                        anchors.margins: 50
                        color: "#E7E6FA"
                    }
                }
        Tab{
            title: qsTr("Agregar al inventario")

            AddItemFrom{
                anchors.fill: parent
                anchors.margins: 4
            }


        }
        Tab{
            title: qsTr("Registar ventas")
            AddSalesItem{
                anchors.fill: parent
            }

        }
        Tab{
            title: qsTr("Reporte de ventas")
            SalesReportForm{
                anchors.fill: parent
            }
        }
    }

}
