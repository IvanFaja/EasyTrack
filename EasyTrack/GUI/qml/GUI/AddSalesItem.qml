import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1
import "qrc:/qml/GUI"

Item {
    id : root

    function updateSearchTabe(){
        itemManager.reset()
        itemManager.reference = refInput.value
        itemManager.size = sizeInput.value
        itemManager.load()
    }

    function updateItemManager(){
        itemManager.reference = refInput.value
        itemManager.amount = amountInput.value
        itemManager.size = sizeInput.value
        itemManager.price = priceInput.value
        itemManager.color = colorInput.value
        itemManager.proveedor = provInput.value
    }
    function setDefaultValues(){
        refInput.value = ""
        provInput.value = "NA"
        priceInput.value = 0
        sizeInput.value = ""
        amountInput.value =1;
        colorInput.value = "NA"
    }
    Column {
        id: container
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.fill: parent
        anchors.margins: 10
        spacing: 6
        Component.onCompleted: {
            setDefaultValues()
        }
        TableView{
            id: data
            width: parent.width
            height: parent.height /2
            model: itemReadOnlyModel
            TableViewColumn{role: "prov"  ; title: qsTr("Proveedor") ; width: 100}
            TableViewColumn{role: "ref"  ; title: qsTr("Refecencia") ; width: 100}
            TableViewColumn{role: "size"  ; title: qsTr("Talla") ; width: 100}
            TableViewColumn{role: "color"  ; title: qsTr("Color") ; width: 100}
            TableViewColumn{
                role: "amount"
                title: qsTr("Cantidad")
                width: 100
            }
            TableViewColumn{role: "price"  ; title: qsTr("Precio") ; width: 100}

            onClicked: {
                refInput.value = data.model.getProperty(row).ref
                provInput.value = data.model.getProperty(row).prov
                priceInput.value = 0
                sizeInput.value = data.model.getProperty(row).size
                amountInput.value = 1
                colorInput.value = data.model.getProperty(row).color
                amountInput.forceActiveFocus()
            }
        }

        Flickable{
            width: parent.width
            height: parent.height /3
            contentWidth : fields.width
            contentHeight: fields.height
            flickableDirection: Flickable.VerticalFlick
            clip: true
            Flow {
                id:fields
                width: container.width -margin
                property int  margin: 15
                InputBox {
                    id: provInput
                    label: qsTr("Proveedor")
                    value:""
                    KeyNavigation.tab: refInput
                    onAcepted: refInput.forceActiveFocus()
                    focus: true
                }
                InputBox {
                    Layout.fillWidth: true
                    id: refInput
                    label: qsTr("Refecencia")
                    value:""
                    KeyNavigation.tab: colorInput
                    onAcepted: colorInput.forceActiveFocus()
                    focus: true
                }
                InputBox {
                    Layout.fillWidth: true
                    id: colorInput
                    label: qsTr("Color")
                    KeyNavigation.tab: sizeInput
                    onAcepted: sizeInput.forceActiveFocus()
                }
                InputBox {
                    Layout.fillWidth: true
                    id: sizeInput
                    label: qsTr("Talla")
                    value:""
                    onAcepted: amountInput.forceActiveFocus()
                    KeyNavigation.tab: amountInput

                }
                InputBox {
                    Layout.fillWidth: true
                    id: amountInput
                    label: qsTr("Cantidad")
                    KeyNavigation.tab: priceInput
                    onAcepted: priceInput.forceActiveFocus()
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{bottom: 0}
                }
                InputBox {
                    Layout.fillWidth: true
                    id: priceInput
                    label: qsTr("Precio")
                    KeyNavigation.tab: save
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{bottom: 0; decimals: 2}
                    onAcepted: save.forceActiveFocus()
                }
            }
        }
        Item {
            id: name
            width: parent.width
            height: childrenRect.height
            Row{
                anchors.left: parent.left
                anchors.verticalCenter: parent.Center
                Button{
                    id: load
                    text: qsTr("Buscar")
                    onClicked: {
                        updateSearchTabe();
                    }
                }
                Button{
                    id: cancel
                    text: qsTr("Limpiar")
                    onClicked: {
                        refInput.value =""
                        setDefaultValues()
                        updateSearchTabe()
                        refInput.forceActiveFocus()
                    }
                }
            }
            Button{
                id: save
                anchors.right: parent.right
                anchors.verticalCenter: parent.Center
                text: qsTr("Registrar Venta")
                onClicked: {
                    updateItemManager()
                    itemManager.sale()
                    setDefaultValues()
                }
            }

        }

    }
}

