#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>
#include <QtQml>
#include <vector>

#include "trailContainer.h"
using namespace std;
class Export : public QObject {
    Q_OBJECT
    QML_ELEMENT
  public:
    explicit Export(QObject* parent = nullptr);

    Q_PROPERTY(QString appKey READ appKey WRITE setAppKey NOTIFY appKeyChanged)
    Q_PROPERTY(QString hmacKey READ hmacKey WRITE setHmacKey NOTIFY hmacKeyChanged)
    Q_PROPERTY(QString pageRange READ pageRange WRITE setPageRange NOTIFY pageRangeChanged)
    Q_PROPERTY(QString notePath READ notePath WRITE setNotePath NOTIFY notePathChanged)

    QString appKey() const;
    QString hmacKey() const;
    QString pageRange() const;
    QString notePath() const;
    void setAppKey(const QString& appKey);
    void setHmacKey(const QString& hmacKey);
    void setPageRange(const QString& pageRange);
    void setNotePath(const QString& notePath);
    Q_INVOKABLE int getTotalPage();

  signals:
    void appKeyChanged();
    void hmacKeyChanged();
    void pageRangeChanged();
    void notePathChanged();

  public slots:
    void startExport(const int& type);

  private:
    void getData(vector<vector<RattaPoint>>& data, const int& page);
    bool parsePage(vector<int>& pageData);

  private:
    QString mAppKey;
    QString mHmacKey;
    QString mPageRange;
    QString mNotePath;
    int mTotalPage;
};

#endif  // EXPORT_H
