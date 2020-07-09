import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import com.qt.logs 1.0

Window {
    visible: true
    width: 720
    height: 480
    title: qsTr("Log parser")

    color: "#2E2F30"

    Row {
        id: r_filter
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        height: 35
        spacing: 10

        Label {
            text: qsTr("Filter Logs")
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
        }

        TextField {
            id: ti_filter_term
            width: 150
            height: parent.height
            textColor: "black"
            onAccepted: console.debug("Accepted new filter term %0".arg(text))
        }
    }

    GroupBox
    {
        id: gb_results
        //            label: Label {
        //                text: qsTr("Results View")
        //                color: "white"
        //            }

        TableView {
            id: tableView
            headerVisible: true
            alternatingRowColors: false
            sortIndicatorOrder: 0
            frameVisible: false
            sortIndicatorVisible: true

            anchors.fill: parent

            TableViewColumn {
                id: idColumn
                title: "Id"
                role: "id"
                width: 30
            }
            TableViewColumn {
                id: timestampColumn
                title: "Timestamp"
                role: "timestamp"
            }
            TableViewColumn {
                id: messageTypeColumn
                title: "Type"
                role: "messageType"
            }
            TableViewColumn {
                id: messageColumn
                title: "Message"
                role: "message"
                width: 300
            }

            model: SortFilterProxyModel {
                id: proxyModel
                source: logsModel.rowCount() > 0 ? logsModel : null

                sortOrder: tableView.sortIndicatorOrder
                sortCaseSensitivity: Qt.CaseInsensitive
                sortRole: logsModel.rowCount() > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""

                filterString: "*" + ti_filter_term.text + "*"
                filterSyntax: SortFilterProxyModel.Wildcard
                filterCaseSensitivity: Qt.CaseInsensitive
            }

            itemDelegate: Item {
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: "black"
                    elide: styleData.elideMode
                    text: styleData.value
                }
            }
        }

        anchors {
            top: r_filter.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }
}
