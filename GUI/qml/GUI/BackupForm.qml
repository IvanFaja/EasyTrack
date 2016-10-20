import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1

Item {
    id: name

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        anchors.margins: 10
        Button{
            text: qsTr("Hacer copia de seguridad")
            onClicked: backupFileDialog.open()
        }
        Button{
            text: qsTr("Restaurar copia de seguridad")
            onClicked: restoreFileDialog.open()
        }


        FileDialog {
            id: backupFileDialog
            selectMultiple: false
            title: qsTr("Por favor escoja una ruta")
            onAccepted: {
                console.log("saved on"+fileUrl)
                itemManager.backup(fileUrl)
            }

            selectFolder: true
            onFileUrlChanged: {

            }
            Component.onCompleted: {
                folder = itemManager.deaultBackUpPath()
            }

        }
    }
}
