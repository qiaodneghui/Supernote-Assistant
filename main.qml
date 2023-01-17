import QtQuick
import Http 1.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Supernote Assistant")
    //    flags: Qt.Window | Qt.FramelessWindowHint  隐藏顶部bar
    signal startHttp
    HttpClient{
        id:http
    }


    Rectangle {
        id: changePasswordRect
        anchors.fill: parent
        anchors.centerIn: parent.center
        color: "#373250";
        MouseArea {
            id: tempMouse
            anchors.fill: parent;
            onClicked: {
                console.log("tempMouse====================================")
            }
        }

        ColumnLayout{
            anchors.centerIn: parent
//            spacing: 20
            //请输入appKey
            TextField {
                id: inputOrgPasswd
    //            anchors.horizontalCenter: parent.horizontalCenter
//                anchors.top: parent.top; anchors.topMargin: 0
//                anchors.left: parent.left; anchors.leftMargin: 110
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
                id: inputNewPasswd
                anchors.top: inputOrgPasswd.bottom;anchors.topMargin: 20
    //            anchors.horizontalCenter: parent.horizontalCenter
//                anchors.top: parent.top; anchors.topMargin: 120
//                anchors.left: parent.left; anchors.leftMargin: 110;
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
                id: confirmButtonRect
                width: 280; height: 48;
                color: "#FF5362"
                radius: 4
                 anchors.top: inputNewPasswd.bottom;anchors.topMargin: 60
//                anchors.top: parent.top; anchors.topMargin: 263
//                anchors.left: parent.left; anchors.leftMargin: 110
                Text {
                    id: confirmText
                    width: parent.width; height: 22
                    color: "#FFFFFF"
                    font.pixelSize: 16
                    font.family: "微软雅黑"
                    anchors.centerIn: parent
                    text: qsTr("确认")
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    id: changePasswdConfirmMouse
                    anchors.fill: parent;
                    onClicked: {
                        var orgPasswd = inputOrgPasswd.text;
                        var newPasswd = inputNewPasswd.text;
                        var newPasswdAgain = inputPasswdAgain.text
                        console.log("changePasswdConfirmMouse=orgPasswd=" + orgPasswd + "=newPasswd=" + newPasswd + "=newPasswdAgain=" + newPasswdAgain)

                    }
                }
            }
        }



        function initChangePasswordUI()
        {
            inputOrgPasswd.text = "";
            inputNewPasswd.text = "";
            inputPasswdAgain.text = "";
        }

    }
}
