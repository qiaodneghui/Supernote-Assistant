import QtQuick
import Assistant 1.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs
Window {
    id: root
    width: 640
    height: 480
    visible: true
    maximumHeight: 480
    maximumWidth: 640
    color: "#373250"
    title: qsTr("Supernote Assistant")

    Export{
        id:exportObj
        appKey: ""
        hmacKey: ""
        pageRange: ""
        notePath: ""
    }
    FirstView{
        id:firstView
        visible: true
        onButtonClicked:function(appKey,hmacKey) {
            exportObj.appKey = appKey
            exportObj.hmacKey = hmacKey
            firstView.visible=false
            secondView.visible=true
        }
    }

    SecondView{
        id:secondView
        visible: false
        onLast:{
            exportObj.notePath = ""
            exportObj.pageRange = ""
            firstView.visible=true
            secondView.visible=false
        }
        onConfirm:{
            exportObj.notePath = secondView.mNotePath
            exportObj.pageRange = secondView.mPageRange
            exportObj.startExport(1);
        }
        onOpen:{
            fileDialog.open()
        }
    }



    FileDialog {
        id: fileDialog

        title: "Please choose a file"

        onAccepted: {
            console.log("You chose: " + fileDialog.OpenFile.toString())

            //Do the data_client stuff and get the file moving
//            client.getUploadFile(fileUrls)
        }
//        onRejected: {
//            console.log("Canceled")
//        }
    }
}
