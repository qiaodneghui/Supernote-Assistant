import QtQuick
import Http 1.0
Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Supernote Assistant")
    signal startHttp
    HttpClient{
        id:http
    }

    Rectangle{
        width: 300
        height: 100
        visible: true
        color:"#F0000c"

        Text {
            id: name
            anchors.fill: parent
            text: qsTr("text")
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                var str="12312";
                http.httpRequestPost(str);
            }
        }
    }
}
