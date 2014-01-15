import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import "../GUI"
ColumnLayout {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.fill: parent
    anchors.margins: 10

    InputBox {
        Layout.fillWidth: true
        id: refInput
        label: qsTr("Refecencia")
        value:""
        KeyNavigation.tab: sizeInput
        onAcepted: sizeInput.forceActiveFocus()
        focus: true
    }
    InputBox {
        Layout.fillWidth: true
        id: sizeInput
        label: qsTr("Talla")
        value:""
        onAcepted: amountInput.forceActiveFocus()
        KeyNavigation.tab: amountInput

    }
    PickerBox {
        Layout.fillWidth: true
        id: amountInput
        label: qsTr("Cantidad")
        KeyNavigation.tab: priceInput
        Keys.onEnterPressed: priceInput.forceActiveFocus()

    }
    PickerBox {
        Layout.fillWidth: true
        id: priceInput
        label: qsTr("Cantidad")
        KeyNavigation.tab: save
        decimals: 2
        minValue: 0
        prefix: "$"
        stepSize : 0.1
    }
    TableView{
        id: data
        Layout.fillWidth: true
        model: itemReadOnlyModel
        TableViewColumn{role: "ref"  ; title: qsTr("Refecencia") ; width: 100}
        TableViewColumn{role: "size"  ; title: qsTr("Talla") ; width: 100}
        TableViewColumn{
            role: "amount"
            title: qsTr("Cantidad")
            width: 100
            horizontalAlignment: Text.AlignHCenter

        }
        TableViewColumn{role: "price"  ; title: qsTr("Precio") ; width: 100}
    }
    RowLayout{
        Button{
            id: save
            text: qsTr("Agregar")
            onClicked: {
                itemManager.reference = refInput.value
                itemManager.amount = amountInput.value
                itemManager.size = sizeInput.value
                itemManager.price = priceInput.value
                itemManager.save()
                itemManager.amount = 1
                priceInput.value = 0
                itemManager.size =""
                sizeInput.value = ""
                amountInput.value =1;
                refInput.forceActiveFocus()
            }
        }
        Button{
            id: load
            text: qsTr("Buscar")
            onClicked: {
                itemManager.reference = refInput.value
                itemManager.size = sizeInput.value
                itemManager.load()
            }
        }
        Button{
            id: sold
            text: qsTr("Registrar Venta")
            onClicked: {
                itemManager.reference = refInput.value
                itemManager.amount = amountInput.value
                itemManager.size = sizeInput.value
                itemManager.price = priceInput.value
                itemManager.sale()
                itemManager.reset()
                priceInput.value = 0
                sizeInput.value = ""
                amountInput.value =1;
                refInput.forceActiveFocus()
            }
        }
    }
}

