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
            objectName: "tabView"
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
                   TableViewColumn{ role: "date"  ; title: "Date" ; width: 100 }
                   TableViewColumn{ role: "timespan" ; title: "Timespan" ; width: 100 }
                   TableViewColumn{ role: "download"  ; title: "Download" ; width: 150 }
                   TableViewColumn{ role: "upload" ; title: "Upload" ; width: 150 }
                   model: hourlyModel
                   sortIndicatorVisible: true
                   sortIndicatorColumn: 0
                   sortIndicatorOrder: Qt.DescendingOrder
                }
            }
            Tab {
                title: "Settings"
                anchors.margins: 10
                active: true
                Column {
                    Layout.fillWidth: true
                    GroupBox {
                        title: "Quota"
                        Layout.fillWidth: true
                        ColumnLayout {
                            Layout.fillWidth: true
                            RowLayout {
                                spacing: 10
                                ColumnLayout {
                                    RowLayout {
                                        CheckBox {
                                            objectName: "quotaEnabled"
                                            text: "Enabled"
                                            checked: false
                                        }
                                        ComboBox {
                                            objectName: "quotaType"
                                            model: quotaModel
                                            textRole: "display"
                                            Layout.fillWidth: true
                                        }
                                    }
                                    RowLayout {
                                        TextField {
                                            objectName: "quotaAmount"
                                            inputMask: "D000000000"
                                            inputMethodHints: Qt.ImhDigitsOnly
                                            text: ""
                                        }
                                        ComboBox {
                                            objectName: "quotaUnit"
                                            model: unitsModel
                                            textRole: "display"
                                            Layout.fillWidth: true
                                        }
                                    }
                                }

                            }
                            Label {
                                objectName: "quotaStatus"
                                text: "Status: Ok"
                            }
                        }
                    }
                }
            }
        }
    }
}
