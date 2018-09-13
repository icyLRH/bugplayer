#include "player.h"
#include "songsdata.h"
#include <QBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include "lyricdownload.h"
#include "skin.h"


#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif


#define m_nBorder 4


Player::Player(QWidget *parent)
    : QWidget(parent),
     m_skinMode(0)
{

    resize(1060,655);
    setMinimumSize(800,600);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    //tray
    setTray(new Tray (this));
    connect(tray(),&QSystemTrayIcon::activated,this,&Player::onActivated);

    setWindowIcon(tray()->icon());

    //frame
    setFrameOfBottom(new FrameOfBottom(this));
    setFrameOfTop(new FrameOfTop(this));

    //playTab
    setPlayTab(new PlayTab(this));

    //lyric
    setLyric(new Lyric (this));

    //connect tray, lrc, mode
    connect(tray()->trayMenu(),&TrayMenu::openLrcAction,lyric()->lyricDialog,&LyricDialog::openLrc);
    connect(tray()->trayMenu(),&TrayMenu::lockLrcAction,lyric()->lyricDialog,&LyricDialog::lockLrc);

    //connect name-artist, tooltip
    connect(playTab()->listTab(),&ListTab::nameAndArtist,tray(),&Tray::setToolTips);
    //connect lrc, btn
    connect(frameOfBottom()->lrcOpenBtn(),&QPushButton::clicked,lyric()->lyricDialog,&LyricDialog::openLrc);

    //network
    Network *network = new Network(this);
    LyricDownload *lyrdownload = new LyricDownload(this);
    connect(playTab()->webTab(),&WebTab::sendLyric,lyrdownload,&LyricDownload::getLyric);//lyq 9/5
    connect(frameOfTop(),&FrameOfTop::sendText,network,&Network::searchReceived);   //network search connect
    connect(frameOfTop(),&FrameOfTop::sendText,playTab(),&PlayTab::webSearched);    //WebTab connect
    connect(frameOfTop(),&FrameOfTop::sendText2,playTab(),&PlayTab::localSearched);  //defaultTab connect
    connect(network,&Network::sendNetResult,playTab()->webTab(),&WebTab::getList);  //newwork result connect

    //layout
    QBoxLayout *boxLayout = new QBoxLayout(QBoxLayout::BottomToTop,this);
    boxLayout->setContentsMargins(m_nBorder,m_nBorder,m_nBorder,m_nBorder);
    boxLayout->setSpacing(0);
    //bottomframe
    boxLayout->addWidget(frameOfBottom());
    //playtab
    boxLayout->addWidget(playTab());
    //topframe
    boxLayout->addWidget(frameOfTop());

    //client
    setCheckMainWindow(new CheckinMainWindow (this));
    connect(frameOfTop(),&FrameOfTop::loging,this,&Player::log);
    //process listTab & auto change to listTab
    connect(checkMainWindow(),&CheckinMainWindow::login,playTab()->listTab(),&ListTab::flash);
    connect(checkMainWindow(),&CheckinMainWindow::login,playTab(),&PlayTab::getLogin);

    //horse label
    connect(playTab()->listTab(),&ListTab::nameAndArtist,frameOfTop(),&FrameOfTop::getNameAndArtist);

    //select
    connect(frameOfTop(),&FrameOfTop::selected,playTab()->defaultTab(),&DefaultTab::select);

    //scan
    connect(frameOfTop(),&FrameOfTop::scaned,playTab()->defaultTab(),&DefaultTab::scan);

    //skin
    setSkin(new Skin (this));
    connect(frameOfTop(),&FrameOfTop::skined,skin(),&Skin::show);
    connect(skin()->skinLabel(),&SkinLabel::mouse_pressed,this,&Player::skinning);

}

/*
 * Function Name: skinning
 * Description: change skin
 * Created: 18/09/09
 * Parameter:  mouseLocalPos  QPoint
 *              pointColor  QColor
 * Return Code: VOID
 * Author: Granx
*/
void Player::skinning(QPoint mouseLocalPos, QColor pointColor)
{

    if(pointColor == QColor())
    {
        m_skinMode = 0;
        //set default skin
        QPixmap pixmap(":/image/src/skin/dafault.png");
        QPalette palette = this->palette();
        palette.setBrush(backgroundRole(),QBrush(pixmap.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        setPalette(palette);
    }
    else
    {
        m_skinMode = 1;
        QPalette palette(pointColor);
        palette.setBrush(backgroundRole(),QBrush(pointColor));
        setPalette(palette);
    }
}

int Player::skinMode() const
{
    return m_skinMode;
}

void Player::setSkinMode(int skinMode)
{
    m_skinMode = skinMode;
}

/*
 * Function Name: setBackgroundImage
 * Description: check the skinMode, set background image.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void Player::setBackgroundImage()
{
    if(m_skinMode == 0)
    {
        //background image
        QPixmap pixmap(":/image/src/skin/dafault.png");
        QPalette palette = this->palette();
        palette.setBrush(backgroundRole(),QBrush(pixmap.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        setPalette(palette);
    }
    else
    {
        return;
    }
}

Skin *Player::skin() const
{
    return m_skin;
}

void Player::setSkin(Skin *skin)
{
    m_skin = skin;
}

Player::~Player()
{

}

FrameOfBottom *Player::frameOfBottom() const
{
    return m_frameOfBottom;
}

void Player::setFrameOfBottom(FrameOfBottom *frameOfBottom)
{
    m_frameOfBottom = frameOfBottom;
}

FrameOfTop *Player::frameOfTop() const
{
    return m_frameOfTop;
}

void Player::setFrameOfTop(FrameOfTop *frameOfTop)
{
    m_frameOfTop = frameOfTop;
}

PlayTab *Player::playTab() const
{
    return m_playTab;
}

void Player::setPlayTab(PlayTab *playTab)
{
    m_playTab = playTab;
}

/*
 * Function Name: onActivated
 * Description: when click tray, activate player window
 * Created: 18/09/09
 * Parameter: reason    QSystemTrayIcon::ActivationReason
 * Return Code: VOID
 * Author: Granx
*/
void Player::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    {
        showNormal();
        raise();
        activateWindow();
        break;
    }
    default:
        break;
    }
}

/*
 * Function Name: resizeEvent
 * Description: keep backgroundImage
 * Created: 18/09/09
 * Parameter: QResizeEvent *
 * Return Code: VOID
 * Author: Granx
*/
void Player::resizeEvent(QResizeEvent *)
{
    setBackgroundImage();
}


/*
 * Function Name: log
 * Description: show client interface
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void Player::log()
{
    checkMainWindow()->show();

    //show at fixed pos
    checkMainWindow()->move(cursor().pos() - QPoint(checkMainWindow()->width()*0.75,0));

}

/*
 * Function Name: nativeEvent
 * Description: achieve resize at border, frameless
 * Created: 18/09/09
 * Parameter: eventType const QByteArray &
 *              message void *
 *              result  long *
 * Return Code: bool
 * Author: Granx
*/
bool Player::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG *param = static_cast<MSG *>(message);

    switch (param->message)
    {
    case WM_NCHITTEST:
    {
        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

        // if cursor pos at children, ignore
        if (childAt(nX, nY) != NULL)
            return QWidget::nativeEvent(eventType, message, result);

        *result = HTCAPTION;

        // if cursor pos at border, go
        if ((nX > 0) && (nX < m_nBorder))
            *result = HTLEFT;

        if ((nX > this->width() - m_nBorder) && (nX < this->width()))
            *result = HTRIGHT;

        if ((nY > 0) && (nY < m_nBorder))
            *result = HTTOP;

        if ((nY > this->height() - m_nBorder) && (nY < this->height()))
            *result = HTBOTTOM;

        if ((nX > 0) && (nX < m_nBorder) && (nY > 0)
                && (nY < m_nBorder))
            *result = HTTOPLEFT;

        if ((nX > this->width() - m_nBorder) && (nX < this->width())
                && (nY > 0) && (nY < m_nBorder))
            *result = HTTOPRIGHT;

        if ((nX > 0) && (nX < m_nBorder)
                && (nY > this->height() - m_nBorder) && (nY < this->height()))
            *result = HTBOTTOMLEFT;

        if ((nX > this->width() - m_nBorder) && (nX < this->width())
                && (nY > this->height() - m_nBorder) && (nY < this->height()))
            *result = HTBOTTOMRIGHT;

        return true;
    }
    }

    return QWidget::nativeEvent(eventType, message, result);
}


CheckinMainWindow *Player::checkMainWindow() const
{
    return m_checkMainWindow;
}

void Player::setCheckMainWindow(CheckinMainWindow *checkMainWindow)
{
    m_checkMainWindow = checkMainWindow;
}

Tray *Player::tray() const
{
    return m_tray;
}

void Player::setTray(Tray *tray)
{
    m_tray = tray;
}


Lyric *Player::lyric() const
{
    return m_lyric;
}

void Player::setLyric(Lyric *lyric)
{
    m_lyric = lyric;
}


