#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <Qtqml/qqml.h>

#include <QByteArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>
#include <QString>

class HttpClient : public QObject {
    Q_OBJECT
  public:
    explicit HttpClient(QObject* parent = nullptr);
    ~HttpClient();

  signals:
    void sucess(const QString& data);
    void error();

  public slots:
    void httpRequestPost(const QString& data);
    void httpRequestPost(const QString& appKey, const QString& hmacKey, const QString& data);

  private slots:
    void dealNetworkFinisheded(QNetworkReply* reply);

  private:
    QNetworkRequest mHttpRequest;
    QNetworkAccessManager* mNetworkAccessManager;
};

#endif  // HTTPCLIENT_H
