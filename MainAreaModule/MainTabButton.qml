import QtQuick 2.0

Rectangle {
    id: container
    width: 80
    height: 60
    state: ''

    property string text

    Text {
        id: label
        text: container.text
        anchors.centerIn: parent
    }

    states: [
        State {
            name: ''
            PropertyChanges { target: container; gradient: normalGradient }
        },
        State {
            name: "clicked"
            PropertyChanges { target: container; gradient: clickedGradient }
        },
        State {
            name: "hover"
            PropertyChanges { target: container; gradient: hoverGradient }
        }

    ]

    Gradient {
        id: normalGradient
        GradientStop { position: 0.0; color: "#000000" }
        GradientStop { position: 1.0; color: "#FFFFFF" }
    }

    Gradient {
        id: hoverGradient
        GradientStop { position: 0.0; color: "#BBBBBB" }
        GradientStop { position: 1.0; color: "#FFFFFF" }
    }

    Gradient {
        id: clickedGradient
        GradientStop { position: 0.0; color: "#666666" }
        GradientStop { position: 1.0; color: "#FFFFFF" }
    }
}
