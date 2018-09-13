#ifndef NETWORK_H
#define NETWORK_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QTextCodec>

class Network : public QWidget
{
    Q_OBJECT
public:
    explicit Network(QWidget *parent = nullptr);
    void parseXml(QString xml);
    void gainSongUrl(QString songid);
    QString parseJson(QString json);
    QString getValueBykey(QJsonObject obj, QString key);

    QString getStrname() const;
    void setStrname(const QString &value);

    QString getStrlenth() const;
    void setStrlenth(const QString &value);

    QString getStrartist() const;
    void setStrartist(const QString &value);

    QString getStralbum() const;
    void setStralbum(const QString &value);

    QString getStrurl() const;
    void setStrurl(const QString &value);

    QString getStrsongid() const;
    void setStrsongid(const QString &value);
    QStringList namelist;
    QStringList lenthlist;
    QStringList artistlist;
    QStringList albumlist;
    QStringList urllist;
    QStringList songidlist;
signals:
    void sendNetResult(QStringList,QStringList,QStringList,QStringList,QStringList);


public slots:
    void searchReceived(QString);
    void replyFinished(QNetworkReply *reply);


private:
    QString strname;
    QString strlenth;
    QString strartist;
    QString stralbum;
    QString strurl;
    QString strsongid;



};

#endif // NETWORK_H
