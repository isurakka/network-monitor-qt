import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Network Monitor")
    objectName: "asd2"

    ColumnLayout {
        width: parent.width
        height: parent.height

        RowLayout {
            width: parent.width - 20
            Label {
                text: "Network interface"
            }

            ComboBox {
                objectName: qsTr("interfaces")
                model: interfacesModel
                textRole: "display"
                Layout.fillWidth: true
            }
            ComboBox {

            }
        }
        TabView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Tab {
                title: "Overview"
                Rectangle { color: "red" }
            }
            Tab {
                title: "Hourly"
                Rectangle { color: "blue" }
            }
            Tab {
                title: "Settings"
                Rectangle { color: "green" }
            }
        }
    }
}
