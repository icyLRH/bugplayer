#ifndef PLAYLISTTAB_H
#define PLAYLISTTAB_H

#include "defaulttable.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
class WebTab : public DefaultTable
{
    Q_OBJECT
public:
    explicit WebTab(QWidget *parent = nullptr);

    QStringList namelist;
    QStringList lengthlist;
    QStringList artistlist;
    QStringList albumlist;
    QStringList songidlist;
    QStringList songurllist;
    QStringList lyrlinklist;
    QStringList codelist;
    void dealStringlist(QStringList &list);
    void lyrDownload(QString, QString name);
    QString transfer(QString);


signals:
    void getListOk(void);    
    void getUrlOk(void);
    void getAUrlOk(void);

    void sendLyric(QStringList, QStringList);


public slots:
    void getList(QStringList name, QStringList lenth, QStringList artist, QStringList album, QStringList id);
    void gainSongUrl(QString);
    void sidReplyFinished(QNetworkReply *reply);

    void startAddItems(void);
    void parseJson(QString);
    void getSongList(void);

    QString getValueBykey(QJsonObject obj, QString key);
    double getTimeBykey(QJsonObject obj, QString key);
    QString getLrcBykey(QJsonObject obj, QString key);


private:


};

#endif // PLAYLISTTAB_H
