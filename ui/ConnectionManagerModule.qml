import QtQuick 2.3
import "qrc:///components/ui" as Components

Item {
  id: form
  visible: opacity !== 0

  property bool connected: window.connected
  onConnectedChanged: {
    if(connected) hideAnimation.start()
    else showAnimation.start()
  }

  NumberAnimation {
    id: hideAnimation
    target: form
    properties: "opacity"
    to: 0
    from: 1
    duration: 100
    easing.type: Easing.InQuad
  }

  NumberAnimation {
    id: showAnimation
    target: form
    properties: "opacity"
    to: 1
    from: 0
    duration: 100
    easing.type: Easing.InQuad
  }

  Rectangle {
    anchors.fill: parent
    color: "#FFFFFF"
    opacity: 0.5
  }

  MouseArea {
    anchors.fill: parent
    onPressed: {}
    onReleased: {}
  }

  Rectangle {
    anchors.centerIn: parent
    width: 350; height: 120
    color: "#242424"
    radius: 5

    Grid {
      id: row
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: parent.top
      anchors.margins: 14
      columns: 2
      columnSpacing: 14
      rowSpacing: 4
      z: 1

      Components.PortsDropdown {
        id: comDropdown
        width: parent.width - connectButton.width - 14
        dataModel: window.availablePorts
        z: 1
      }

      Components.StandardButton {
        id: connectButton
        width: 80
        text: qsTr("Connect")
        onClicked: window.connectToPortClicked(comDropdown.text, "3")
      }

      Components.Label {
        width: comDropdown.width
        text: qsTr("Port")
        verticalAlignment: Text.AlignHCenter
        color: "#FFFFFF"
      }
    }

    Components.VerticalSeparator {
      id: separator
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.top: row.bottom
      anchors.margins: 14
    }

    Text {
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      anchors.top: separator.bottom
      anchors.margins: 14
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter

      font.family: fontRoman.name
      font.pixelSize: 14
      color: "#FFFFFF"
      wrapMode: Text.Wrap

      text: qsTr("<font color='#7F7F7F'>Choose connection port and press</font> <font color='#FFFFFF'><b>Connect</b></font>")
    }
  }
}
