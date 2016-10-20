import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1


Rectangle{
    width: 300
    height: 50
    RowLayout{
        anchors.fill: parent
    ScrollView{

        ListView{
            model:ListModel{

                ListElement {
                    name: "Bill Smith"
                    number: "555 3264"
                }
                ListElement {
                    name: "John Brown"
                    number: "555 8426"
                }
                ListElement {
                    name: "Sam Wise"
                    number: "555 0473"
                }
            }
            delegate:
                Text {
                    text: name

            }
        }
    }
    }
}

