import QtQuick 2.0
import QtQuick.Controls 1.1

ApplicationWindow {

    id: root
    width: 300
    height: 300
    menuBar:
    MenuBar{

    Menu{
        id:rootMenu
        MenuItem{
            text: "Agregar Items"
            onTriggered: pageLoader.source = "AddItemFrom.qml"
        }
        MenuItem{
            text: "Registrar Ventas"
        }
        MenuItem{
            text: "Reportes"
        }

    }
    }
    Rectangle{
        id:header
        width: parent.width
        height: headesOptions.height
        Row{
            id:headesOptions
            Rectangle{
                height: 30
                width: 30
                color: "red"
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        rootMenu.popup()
                    }
                }
            }
        }
    }
    Loader{
        anchors.top: header.bottom
        width: parent.width
        height: parent.height - header.height
        id: pageLoader
        source:""
    }
}
