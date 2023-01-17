#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QString>
#include<QObject>
#include<QJsonObject>
#include<QByteArray>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);
    ~HttpClient();
signals:
    void sucess(const QString& data);
    void error();

public slots:
     void httpRequestPost(const QString &data);
     void httpRequestPost(const QString &appKey,const QString &hmacKey,const QString &data);

private slots:
     void dealNetworkFinisheded(QNetworkReply *reply);

private:
     QNetworkRequest mHttpRequest;
     QNetworkAccessManager *mNetworkAccessManager;
};

#endif // HTTPCLIENT_H
