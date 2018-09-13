#ifndef PLAYER_H
#define PLAYER_H

#include"frameofbottom.h"
#include"frameoftop.h"
#include"playtab.h"
#include"tray.h"
#include"lyric.h"
#include <QWidget>
#include<QSystemTrayIcon>
#include"network.h"
#include"checkinmainwindow.h"
#include "skin.h"
class QSystemTrayIcon;

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = 0);
    ~Player();

    FrameOfBottom *frameOfBottom() const;
    void setFrameOfBottom(FrameOfBottom *frameOfBottom);

    FrameOfTop *frameOfTop() const;
    void setFrameOfTop(FrameOfTop *frameOfTop);

    PlayTab *playTab() const;
    void setPlayTab(PlayTab *playTab);

    Lyric *lyric() const;
    void setLyric(Lyric *lyric);

    Tray *tray() const;
    void setTray(Tray *tray);

    void setBackgroundImage();
    CheckinMainWindow *checkMainWindow() const;
    void setCheckMainWindow(CheckinMainWindow *checkMainWindow);

    void setSkin(Skin *skin);
    Skin *skin() const;

    int skinMode() const;
    void setSkinMode(int skinMode);

public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);

    void resizeEvent(QResizeEvent *);

    void log(void);

    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    void skinning(QPoint mouseLocalPos, QColor pointColor);

private:
    FrameOfBottom *m_frameOfBottom;
    FrameOfTop *m_frameOfTop;
    PlayTab *m_playTab;

    Lyric *m_lyric;

    Tray *m_tray;

    CheckinMainWindow *m_checkMainWindow;

    Skin *m_skin;
    int m_skinMode;

};

#endif // PLAYER_H
