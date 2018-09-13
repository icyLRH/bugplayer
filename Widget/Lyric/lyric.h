#ifndef LYRIC_H
#define LYRIC_H

#include <QWidget>
#include "lyricloader.h"
#include "lyricdialog.h"

class Lyric : public QWidget
{
    Q_OBJECT
public:
    explicit Lyric(QWidget *parent = nullptr);
    explicit Lyric( QString url,QWidget *parent = nullptr);

    bool openLyric(QString url);
    bool startLyric(qint64 time);

    QString url;
    QString qLrc;
    QString currentLine;

    LyricLoader *lyricLoader;
    LyricDialog *lyricDialog;

    int lastResult;       //next start line

    qint64 totalTime;      //song's duration

signals:
    void sendCurrentLine(QString,qint64 time);
    void flagState(int);


public slots:
    void getCurrentms(qint64 ms);
    void startANew();
    void flagWatch(int state);

private:

};

#endif // LYRIC_H
