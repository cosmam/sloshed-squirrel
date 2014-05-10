import QtQuick 2.0
import QtQuick.Controls 1.1 as Controls
import QtQuick.Controls.Styles 1.1 as Styles
import QtQuick.Dialogs 1.1 as Dialogs

Item {
    id: rootItem
    anchors.fill: parent
    anchors.margins: 10

    signal process

    Item {
        id: directoryContainer
        anchors { left: parent.left; top: parent.top; right: parent.right }
        height: 30
        anchors.topMargin: 20

        Text {
            id: directoryLabel
            anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
            text: "Project Directory:"
            verticalAlignment: Text.AlignVCenter
        }

        Controls.TextField {
            id: directoryInput
            objectName: "directoryInput"
            anchors { left: directoryLabel.right; top: parent.top; bottom: parent.bottom; right: directoryButton.left }
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            style: Styles.TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    radius: 2
                    width: directoryInput.width
                    border.color: "#333333"
                    border.width: 1
                    color: "#FFFFFF"
                }
            }
        }

        Controls.Button {
            id: directoryButton
            anchors { top: parent.top; right: parent.right; bottom: parent.bottom }
            width: 75
            text: "Select..."

            onClicked: {
                if( directoryInput.text.length !== 0 ) {
                    fileDialog.folder = Qt.resolvedUrl(directoryInput.text)
                }
                fileDialog.open()
            }
        }
    }

    Item {
        id: fileTypesContainer
        anchors { left: parent.left; top: directoryContainer.bottom; right: parent.right }
        height: 30
        anchors.topMargin: 20

        Text {
            id: fileTypesLabel
            anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
            width: directoryLabel.width
            text: "File Types:"
            verticalAlignment: Text.AlignVCenter
        }

        Controls.TextField {
            id: fileTypesInput
            objectName: "fileTypesInput"
            anchors { left: fileTypesLabel.right; top: parent.top; bottom: parent.bottom; right: parent.right }
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            style: Styles.TextFieldStyle {
                textColor: "black"
                background: Rectangle {
                    radius: 2
                    width: fileTypesInput.width
                    border.color: "#333333"
                    border.width: 1
                    color: "#FFFFFF"
                }
            }
        }
    }

    Item {
        id: outputOptionsContainer
        anchors { left: parent.left; top: fileTypesContainer.bottom; right: parent.right }
        height: 20
        anchors.topMargin: 20

        Text {
            id: outputOptionsLabel
            anchors { left: parent.left; top: parent.top; bottom: parent.bottom }
            width: directoryLabel.width
            text: "Output Options:"
            verticalAlignment: Text.AlignVCenter
        }

        Controls.CheckBox {
            id: fileOutput
            objectName: "fileOutput"
            anchors { left: outputOptionsLabel.right; top: parent.top; bottom: parent.bottom }
            width: 100
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            checked: true
            text: "File Analysis"
        }

        Controls.CheckBox {
            id: classOutput
            objectName: "classOutput"
            anchors { left: fileOutput.right; top: parent.top; bottom: parent.bottom }
            width: 100
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            checked: true
            text: "Class Analysis"
        }
    }
    Item {
        id: processContainer
        anchors { left: parent.left; top: outputOptionsContainer.bottom; right: parent.right }
        height: 30
        anchors.topMargin: 20

        Controls.Button {
            id: processButton
            objectName: "processButton"
            anchors { top: parent.top; bottom: parent.bottom; right: processContainer.right }
            width: 100
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            text: "Process"
            enabled: (directoryInput.text.length !== 0 && fileTypesInput.text.length !== 0)
        }
    }

    ResultsSummary {
        id: resultsSummary
        objectName: "resultsSummary"
        anchors { left: parent.left; top: processContainer.bottom; right: parent.right; bottom: parent.bottom }
        anchors.topMargin: 20
        visible: false
    }

    Dialogs.FileDialog {
        id: fileDialog
        selectFolder: true
        title: "Please choose project directory..."
        visible: false

        onAccepted: {
            directoryInput.text = fileDialog.folder.toString().slice(7, fileDialog.folder.toString().length)
            visible = false
        }

        onRejected: { visible = false }
    }
}
