import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1

Column {
    property bool confirmed: false
    property int rowToDele: 0;

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.fill: parent
    anchors.margins: 10
    Component.onCompleted: {
        sales.loadSalesDates();
    }

    function updateSales(){

        sales.reportFilter = salesDatefilterInput.currentText;
        sales.loadSalesReport();
        sales.loadSalesDates();

    }
    Column {
        id: head
        ComboBox{
            id: salesDatefilterInput
            model: salesDatesModel
            textRole: "yearMonth"
            onAccepted:sales.loadSalesReport();
        }
    }

    MessageDialog{
        id: confirmDialog
        standardButtons: StandardButton.Yes | StandardButton.Cancel
        onYes:{ confirmed =true; visible = false
            salesReportModel.removeRow(rowToDele)
            updateSales();
        }
        onRejected: {confirmed =false; visible = false}
    }


    TableView{

        id: data
        width: parent.width
        height: parent.height - head.height - foot.height -10
        model: salesReportModel
        TableViewColumn{role: "delete"  ; title: qsTr("") ; width: 60
            delegate:
                Button{
                text: qsTr("Borrar")
                onClicked: {
                    rowToDele = styleData.row
                    confirmDialog.text =qsTr("Esta seguro que desea borrar la venta?")
                    confirmDialog.open();
//                    confirmDialog.informativeText = styleData.value

                }
            }

        }

        TableViewColumn{role: "prov"  ; title: qsTr("Proveedor") ; width: 100}
        TableViewColumn{role: "date"  ; title: qsTr("Fecha") ; width: 100}
        TableViewColumn{role: "ref"  ; title: qsTr("Refecencia") ; width: 100}
        TableViewColumn{role: "size"  ; title: qsTr("Talla") ; width: 100}
        TableViewColumn{role: "color"  ; title: qsTr("Color") ; width: 100}
        TableViewColumn{
            role: "amount"
            title: qsTr("Cantidad")
            width: 100
        }
        TableViewColumn{role: "price"  ; title: qsTr("Precio de venta") ; width: 100
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
        TableViewColumn{role: "buyPrice"  ; title: qsTr("Precio de compra") ; width: 100}
        TableViewColumn{role: "profit"  ; title: qsTr("Ganancia") ; width: 100}

    }
    Column {
        id: foot
        Row{
            Text {
                text: qsTr("Ganacias totales:")
            }
            Text {
                id: profitTotal
                text: sales.totalProfit
            }
        }
        Row{
            Text {
                text: qsTr("Ventas totales:")
            }
            Text {
                id: salesTotal
                text: sales.totalSales
            }
        }
        Button{
            id: load
            text: qsTr("Actualizar")
            onClicked: {
                updateSales();
            }
        }
    }

}
