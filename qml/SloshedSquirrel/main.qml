import QtQuick 2.1
import QtQuick.Controls 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        id: tabView
        anchors.fill: parent

        Component.onCompleted: {
            addTab("Setup", Qt.createComponent("Setup.qml"));
            addTab("Results", Qt.createComponent("Results.qml"));
        }
    }

    ProcessProgress {
        id: progressDialog
        objectName: "progressDialog"
        anchors.fill: parent
        visible: false
    }
}
