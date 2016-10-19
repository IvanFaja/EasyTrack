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
        priceInput.value = 0
        sizeInput.value = ""
        amountInput.value =1;
        colorInput.value = "NA"
        provInput.value= "NA"
    }

    Column{
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
            TableViewColumn{role: "price"  ; title: qsTr("Precio") ; width: 100
                delegate: Item {

                    Text {
                        width: parent.width
                        anchors.margins: 4
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        elide: styleData.elideMode
                        text: styleData.value !== undefined ? styleData.value : ""
                        color: styleData.textColor
                        visible: !styleData.selected
                    }
                    Loader { // Initialize text editor lazily to improve performance
                        id: loaderEditor
                        anchors.fill: parent
                        anchors.margins: 4
                        Connections {
                            target: loaderEditor.item
                            onAccepted: {
                                model.setProperty(styleData.row, styleData.role, loaderEditor.item.text)
                            }
                        }
                        sourceComponent: styleData.selected ? editor : null
                        Component {
                            id: editor
                            TextInput {
                                id: textinput
                                color: styleData.textColor
                                text: styleData.value
                                validator: DoubleValidator{bottom: 0}
                                inputMethodHints: Qt.ImhFormattedNumbersOnly
                                MouseArea {
                                    id: mouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked: textinput.forceActiveFocus()

                                }
                            }
                        }
                    }
                }
            }
            onClicked: {
                refInput.value = data.model.getProperty(row).ref
                provInput.value = data.model.getProperty(row).prov
                priceInput.value = data.model.getProperty(row).price
                sizeInput.value = data.model.getProperty(row).size
                amountInput.value =data.model.getProperty(row).amount
                colorInput.value = data.model.getProperty(row).color
                provInput.forceActiveFocus()
            }
        }

        ScrollView{
            width: parent.width
            height: parent.height /3
            clip: true
            Flow {
                id:fields
                property int  margin: 15
                width: container.width -margin
                InputBox {
                    id: provInput
                    label: qsTr("Proveedor")
                    value:""
                    KeyNavigation.tab: refInput
                    onAcepted: refInput.forceActiveFocus()
                    focus: true
                }
                InputBox {
                    id: refInput
                    label: qsTr("Refecencia")
                    value:""
                    KeyNavigation.tab: colorInput
                    onAcepted: colorInput.forceActiveFocus()
                    focus: true
                }
                InputBox {
                    id: colorInput
                    label: qsTr("Color")
                    KeyNavigation.tab: sizeInput
                    onAcepted: sizeInput.forceActiveFocus()
                }
                InputBox {
                    id: sizeInput
                    label: qsTr("Talla")
                    value:""
                    onAcepted: amountInput.forceActiveFocus()
                    KeyNavigation.tab:amountInput

                }
                InputBox {
                    id: amountInput
                    label: qsTr("Cantidad")
                    KeyNavigation.tab: priceInput
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    onAcepted: priceInput.forceActiveFocus()
                    validator: IntValidator{bottom: 0}
                }
                InputBox {
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
            id:buttonContainer
            width: parent.width
            height: childrenRect.height
            Row{
                anchors.left: parent.left
                anchors.verticalCenter: parent.Center
                spacing: 5
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
                anchors.verticalCenter: parent.Center
                anchors.right: parent.right
                text: qsTr("Agregar")
                onClicked: {
                    updateItemManager()
                    itemManager.save()
                }
            }
        }
    }
}
