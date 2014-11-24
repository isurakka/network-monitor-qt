import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
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
                text: "Interface"
            }

            ComboBox {
                objectName: "interfaceSelection"
                model: interfacesModel
                textRole: "display"
                Layout.fillWidth: true
            }
            ComboBox {
                objectName: "unitSelection"
                model: unitsModel
                textRole: "display"
            }
        }
        TabView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Tab {
                objectName: "overviewTab"
                title: "Overview"
                ColumnLayout {
                    RowLayout {
                        Label {
                            text: "Download"
                        }
                        Label {
                            objectName: "currentDownloadValue"
                            text: "0"
                        }
                    }
                    RowLayout {
                        Label {
                            text: "Upload"
                        }
                        Label {
                            objectName: "currentUploadValue"
                            text: "0"
                        }
                    }
                }
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
