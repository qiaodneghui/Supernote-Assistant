import QtQuick
import QtQuick.Controls 2.5

Item {

    signal buttonClicked(string appKey, string hmacKey)

    id: firstViewRoot
    visible: true
    anchors.fill: parent
    anchors.centerIn: parent.center

    Image {
        id: logo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        width: 300
        source: "images/logo.png"
        fillMode: Image.PreserveAspectFit
    }

    //请输入appKey
    TextField {
        id: appKey
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: logo.bottom
        anchors.topMargin:40
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
        font.family: "微软雅黑"
        color: "white" //"#B2B2B2"
        cursorVisible: true;
        selectByMouse: true //是否可以选择文本
        selectionColor: "#999999"//选中背景颜色
        placeholderText: qsTr("请输入appKey")
        width: 280; height: 40;
        background: Rectangle {
            border.width: 0; //border.color: "#B2B2B2"
            radius: 4; color: "#FFFFFF" //"transparent"
            opacity: 0.05
            implicitHeight: 40; implicitWidth: 280
        }
    }

    //请输入hmacKey
    TextField {
        id: hmacKey
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: appKey.bottom
        anchors.topMargin: 20
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12;
        font.family: "微软雅黑"
        color: "white"
        //cursorVisible: true;
        selectByMouse: true //是否可以选择文本
        //echoMode: TextInput.Password //密码模式
        selectionColor: "#999999"//选中背景颜色
        placeholderText: qsTr("请输入hmacKey")
        width: 280; height: 40;
        background: Rectangle {
            border.width: 0; border.color: "red"
            radius: 4; color: "#FFFFFF";
            opacity: 0.05
            implicitHeight: 40; implicitWidth: 280
        }
    }

    //确认按钮
    Rectangle {
        id: nextButton
        width: 280; height: 48;
        color: "#FF5362"
        radius: 4
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: hmacKey.bottom
        anchors.topMargin: 40
        Text {
            id: nextText
            width: parent.width; height: 22
            color: "#FFFFFF"
            font.pixelSize: 16
            font.family: "微软雅黑"
            anchors.centerIn: parent
            text: qsTr("下一步")
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            id: nextMouse
            anchors.fill: parent
            onClicked: firstViewRoot.buttonClicked(appKey.text,hmacKey.text)
        }
    }
}
