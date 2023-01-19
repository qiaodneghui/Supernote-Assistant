#include "httpclient.h"

#include <QNetworkReply>

#include "utils.h"
HttpClient::HttpClient(QObject* parent) : QObject{parent} {
    mNetworkAccessManager = new QNetworkAccessManager();

    // 处理所有post请求
    connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &HttpClient::dealNetworkFinisheded);
}

HttpClient::~HttpClient() {
    qDebug() << "~HttpClient";
    delete mNetworkAccessManager;
}

void HttpClient::httpRequestPost(const QString& data) {
    qDebug() << "httpRequestPost";
    //    QJsonObject obj;
    //    obj.insert("accountId", "1");
    //    QJsonDocument jsonDoc(obj);//QJsonObject转QJsonDocument
    //    QString str = QString(jsonDoc.toJson());//QJsonDocument转QString
    //    QByteArray content = str.toUtf8();
    //    int contentLength = content.length();

    // applicationKey:23b2472e-dd16-40c9-8257-02705da687c0
    // hmac:8325F5579316CA45FD9BA4F95161C1F31719145C1D20AA4D7AAB8F199C38A956A4B9323F122CF9B124575CDA41F1A3B2983732B04C8F4731CDF8B2ADB79076D7
    // Content-Type:application/json
    // accept:application/vnd.myscript.jiix
    //     m_httpRequest.setUrl(QUrl(m_requestIPHead + "/api/clientversion/client/working/mode/query"));
    ;
    mHttpRequest.setUrl(QUrl("https://cloud.myscript.com/api/v4.0/iink/batch"));
    mHttpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mHttpRequest.setRawHeader("accept", "application/vnd.myscript.jiix");
    mHttpRequest.setRawHeader("applicationKey", "23b2472e-dd16-40c9-8257-02705da687c0");
    mHttpRequest.setRawHeader("hmac", "8325F5579316CA45FD9BA4F95161C1F31719145C1D20AA4D7AAB8F199C38A956A4B9323F122CF9B1"
                                      "24575CDA41F1A3B2983732B04C8F4731CDF8B2ADB79076D7");

    mNetworkAccessManager->post(mHttpRequest, data.toUtf8());
}

void HttpClient::httpRequestPost(const QString& appKey, const QString& hmacKey, const QString& data) {
    qDebug() << "httpRequestPost"
             << "  appKey:" << appKey << "   hmacKey:" << hmacKey;
    //    QJsonObject obj;
    //    obj.insert("accountId", "1");
    //    QJsonDocument jsonDoc(obj);//QJsonObject转QJsonDocument
    //    QString str = QString(jsonDoc.toJson());//QJsonDocument转QString
    //    QByteArray content = str.toUtf8();
    //    int contentLength = content.length();

    // applicationKey:23b2472e-dd16-40c9-8257-02705da687c0
    // hmac:8325F5579316CA45FD9BA4F95161C1F31719145C1D20AA4D7AAB8F199C38A956A4B9323F122CF9B124575CDA41F1A3B2983732B04C8F4731CDF8B2ADB79076D7
    // Content-Type:application/json
    // accept:application/vnd.myscript.jiix
    //     m_httpRequest.setUrl(QUrl(m_requestIPHead + "/api/clientversion/client/working/mode/query"));

    mHttpRequest.setUrl(QUrl("https://cloud.myscript.com/api/v4.0/iink/batch"));
    mHttpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    mHttpRequest.setRawHeader("accept", "application/vnd.myscript.jiix");
    mHttpRequest.setRawHeader("applicationKey", appKey.toUtf8().data());

    auto s = Utils::getHmac_sha256(data.toStdString(), appKey.toStdString(), hmacKey.toStdString());
    mHttpRequest.setRawHeader("hmac", s.c_str());

    mNetworkAccessManager->post(mHttpRequest, data.toUtf8());
}

void HttpClient::dealNetworkFinisheded(QNetworkReply* reply) {
    QVariant data = reply->readAll();  // 读取全部数据
    const char* s = data.toByteArray().constData();
    qDebug("data:%s", s);
    //        QJsonParseError jsonError;
    //        QJsonDocument document = QJsonDocument::fromJson(data.toByteArray(), &jsonError);
    //        if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
    //              qDebug()<<"解析未发生错误";
    //                qDebug()<<"JSON 文档为对象";
    //                  QJsonObject object = document.object();  // 转化为对象
    //                  if (document.isObject()) {
    //                      switch (m_analysisPostRequestType) {
    //                        case AnalysisPostType::TestRequest:
    //                          dealTestRequest(object);
    //                          break;
    //                      default:
    //                          break;
    //                      }
    //                  }else{
    //                      emit sendDealDataResult(PostStatus::DealDatabaseError, m_executePostRequestType);
    //                  }
    //        }else{
    //            if(document.isNull() == true){
    //                qDebug()<<"document.isNull:" + reply->errorString();
    //                emit sendDealDataResult(PostStatus::SeverDisconnectError, m_executePostRequestType);
    //            }else if(jsonError.error == QJsonParseError::NoError){
    //               qDebug()<<"jsonError.error:" + reply->errorString();
    //               emit sendDealDataResult(PostStatus::SeverDisconnectError, m_executePostRequestType);
    //            }
    //        }
    // 删除对象
    reply->deleteLater();
}
