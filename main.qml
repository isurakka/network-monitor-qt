import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import NetworkMonitor 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Network Monitor")

    ColumnLayout {
        width: parent.width
        height: parent.height
        spacing: 20
        RowLayout {
            id: selectionsRow
            anchors.fill: parent
            anchors.margins: 10
            Label {
                id: ifLab
                text: "Interface"
            }
            ComboBox {
                id: ifSel
                objectName: "interfaceSelection"
                model: interfacesModel
                textRole: "display"
                Layout.fillWidth: true
                anchors.left: ifLab.right
                anchors.leftMargin: 5
                anchors.right: unitSel.left
                anchors.rightMargin: 5
            }
            ComboBox {
                id: unitSel
                objectName: "unitSelection"
                model: unitsModel
                textRole: "display"
                anchors.right: parent.right
            }
        }
        TabView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Tab {
                objectName: "overviewTab"
                title: "Overview"
                anchors.margins: 10
                ColumnLayout {
                    ColumnLayout {
                        RowLayout {
                            Label {
                                text: "DL"
                            }
                            Label {
                                objectName: "currentDownloadValue"
                                text: "0"
                            }
                            Rectangle {
                                Layout.fillWidth: true
                            }
                            Label {
                                objectName: "maxLabel"
                                text: "Max 0"
                            }
                        }
                        NetworkGraph
                        {
                            objectName: "downloadGraph"
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }
                    }
                    ColumnLayout {
                        RowLayout {
                            Label {
                                text: "UL"
                            }
                            Label {
                                objectName: "currentUploadValue"
                                text: "0"
                            }
                            Rectangle {
                                Layout.fillWidth: true
                            }
                            Label {
                                objectName: "maxLabel"
                                text: "Max 0"
                            }
                        }
                        NetworkGraph
                        {
                            objectName: "uploadGraph"
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }
                    }
                }
            }
            Tab {
                title: "Hourly"
                TableView {
                    id: asdd
                   model: hourlyModel
                   sortIndicatorVisible: true
                   TableViewColumn{ role: "date"  ; title: "Date" ; width: 100 }
                   TableViewColumn{ role: "timespan" ; title: "Timespan" ; width: 100 }
                   TableViewColumn{ role: "download"  ; title: "Download" ; width: 150 }
                   TableViewColumn{ role: "upload" ; title: "Upload" ; width: 150 }
                }
            }
            Tab {
                title: "Settings"
                Label {
                    text: "TODO"
                }
            }
        }
    }
}
