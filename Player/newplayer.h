#ifndef NEWPLAYER_H
#define NEWPLAYER_H

#include <QObject>
#include"player.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QPushButton>
#include<QSlider>
#include<QLabel>
#include <QDate>
#include <QTime>
#include <QUrl>
#include <QFileDialog>
#include <QTimer>
#include <QMediaMetaData>
#include"customslider.h"

class NewPlayer : public Player
{
    Q_OBJECT


public:
    explicit NewPlayer(QWidget *parent = 0);



    QMediaPlaylist *getSonglist() const;
    void setSonglist(QMediaPlaylist *songlist);

    QMediaPlayer *getMediaPlayer() const;
    void setMediaPlayer(QMediaPlayer *mediaPlayer);

signals:
    void sendDuration();
    void sendCurrentms(qint64);
    void durationOk();


public slots:
    void PlbtClicked();

    void VosValueChanged(int value);

    void setMediaDuration();    
    qint64 getMediaDuration();

    void updateTime();

    void onTimerOut();
    void onTimer2Out();

    void timSldClicked();
    void timSldMoved();
    void timSldReleased();

    void getUrl(QString url);
    void addConnect(void);      //接收playTab的fresh信号，进行connect添加

    void nextBtnClicked();
    void preBtnClicked();

    void durationReady();

    void startLrc(const QMediaContent &mediaContent);

    void single();
    void random();
    void loop();
    void modeBtnClicked();


private:
    QMediaPlayer *m_mediaPlayer;
    QTimer *timer;
    QTimer *timer2;
    QDate date;
    QTime time1;
    QTime time2;
    qint64 m_totalTime;
    QMediaPlaylist *m_songlist;


};


#endif // NEWPLAYER_H
