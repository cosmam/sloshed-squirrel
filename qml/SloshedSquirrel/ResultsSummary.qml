import QtQuick 2.0
import QtQuick.Layouts 1.1 as Layouts

Item {
    id: rootItem

    property bool displayResults: false

    property int fileCount: 0
    property int totalLines: 0
    property int codeLines: 0
    property int commentLines: 0
    property int headerLines: 0

    property int rowHeight: 20

    Layouts.GridLayout {
        anchors.fill: parent
        id: grid
        columns: 2
        Text { text: "File count:" }
        Text { text: rootItem.fileCount }
        Text { text: "Total lines:" }
        Text { text: rootItem.totalLines }
        Text { text: "Lines of code:" }
        Text { text: rootItem.codeLines }
        Text { text: "Total comment lines:" }
        Text { text: rootItem.headerLines + rootItem.commentLines }
        Text { text: "Header comment lines:" }
        Text { text: rootItem.headerLines }
        Text { text: "Other comment lines:" }
        Text { text: rootItem.commentLines }
    }
}
