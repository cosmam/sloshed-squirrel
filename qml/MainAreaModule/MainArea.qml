import QtQuick 2.0
import QtQuick.Controls 1.0

Item {
    id: mainArea

    Column {
        id: tabMenu
        anchors { top: parent.top; bottom: parent.bottom; left: parent.left }
        width: 80

        MainTabButton {
            id: welcome
            text: "Welcome"
        }
        MainTabButton {
            id: project
            text: "Project"
        }
    }

    StackView {
        id: tabArea
        anchors { top: parent.top; bottom: parent.bottom; right: parent.bottom; left: tabMenu.right }
    }
}
