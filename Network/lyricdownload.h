#ifndef LYRICDOWNLOAD_H
#define LYRICDOWNLOAD_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include "webtab.h"


class LyricDownload : public QWidget
{
    Q_OBJECT
public:
    explicit LyricDownload(QWidget *parent = nullptr);
    QStringList namelist;
    QStringList lyriclist;

signals:
    void lyrOk();
    void setAlready();
    void lastFinished();


public slots:
    void getLyric(QStringList lyrics,QStringList names);
    void lyrReplyFinished(QNetworkReply *reply);
    void lyrDownload();


private:

};

#endif // LYRICDOWNLOAD_H
