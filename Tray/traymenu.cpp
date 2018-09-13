#include "traymenu.h"

#include <QLabel>
#include <QAction>


TrayMenu::TrayMenu(QWidget *parent) : QMenu(parent)
{
    creatActions();

    //connect
    connect(exit(),&QAction::triggered,parentWidget(),&QWidget::close);

    connect(play(),&QAction::triggered,this,&TrayMenu::playAction);
    connect(previous(),&QAction::triggered,this,&TrayMenu::PreAction);
    connect(next(),&QAction::triggered,this,&TrayMenu::nextAction);
    connect(single(),&QAction::triggered,this,&TrayMenu::singleAction);
    connect(order(),&QAction::triggered,this,&TrayMenu::orderAction);
    connect(rand(),&QAction::triggered,this,&TrayMenu::randAction);
    connect(openLrc(),&QAction::triggered,this,&TrayMenu::openLrcAction);
    connect(lockLrc(),&QAction::triggered,this,&TrayMenu::lockLrcAction);
    connect(options(),&QAction::triggered,this,&TrayMenu::optionsAction);

    customStylesSheet();
}

/*
 * Function Name: creatActions
 * Description: creatActions and add them to menu
 * Created: 18/09/09
 * Parameter: name  VOID
 * Return Code: VOID
 * Author: Granx
*/
void TrayMenu::creatActions()
{
    //initialize actions
    setPlay(new QAction(QIcon(":/image/src/trayMenu/menu_play (1).png"),"播放/暂停",this));
    setPrevious(new QAction(QIcon(":/image/src/trayMenu/menu_previous (1).png"),"上一首",this));
    setNext(new QAction (QIcon(":/image/src/trayMenu/menu_next (1).png"),"下一首",this));

    setModeMenu(new QMenu("播放模式",this));
    setSingle(new QAction (QIcon(":/image/src/bottomwidget/btn_listscircle_single (3).png"),"单曲循环",this));
    setOrder(new QAction (QIcon(":/image/src/bottomwidget/btn_listcircle (3).png"),"顺序播放",this));
    setRand(new QAction (QIcon(":/image/src/bottomwidget/btn_listrandom (3).png"),"随机播放",this));

    setOpenLrc(new QAction (QIcon(":/image/src/trayMenu/menu_lrc.png"),"关闭/打开桌面歌词",this));
    setLockLrc(new QAction (QIcon(":/image/src/trayMenu/menu_lock.png"),"解锁/锁定桌面歌词",this));
    setOptions(new QAction (QIcon(":/image/src/trayMenu/menu_setting.png"),"设置",this));

    setExit(new QAction (QIcon(":/image/src/trayMenu/menu_close.png"),"退出",this));

    //add actions
    addAction(play());
    addAction(previous());
    addAction(next());

    addSeparator();

    addMenu(modeMenu());
    modeMenu()->addAction(single());
    modeMenu()->addAction(order());
    modeMenu()->addAction(rand());

    addSeparator();

    addAction(openLrc());
    addAction(lockLrc());
//    addAction(options());
    addAction(exit());



}

/*
 * Function Name: customStylesSheet
 * Description: set styles sheet
 * Created: 18/09/09
 * Parameter: name  VOID
 * Return Code: VOID
 * Author: Granx
*/
void TrayMenu::customStylesSheet()
{

    setStyleSheet("QMenu{background: rgb(255,255,255);"
                        "border: 2px solid transparent;"
                        "margin: 0px}"
                  "QMenu::item{color:#545454;"
                                "background-color:transparent;"
                                "border: 5px solid transparent;"
                                "padding: 2px 25px 2px 20px}"
                  "QMenu::item::selected{color:white;"
                                "background-color:#fdcedf}"
                  "QMenu::separator{height:1px;"
                                "background-color:rgba(220,220,220,200);}");

}


QAction *TrayMenu::play() const
{
    return m_play;
}

void TrayMenu::setPlay(QAction *play)
{
    m_play = play;
}

QAction *TrayMenu::previous() const
{
    return m_previous;
}

void TrayMenu::setPrevious(QAction *previous)
{
    m_previous = previous;
}

QAction *TrayMenu::next() const
{
    return m_next;
}

void TrayMenu::setNext(QAction *next)
{
    m_next = next;
}

QMenu *TrayMenu::modeMenu() const
{
    return m_modeMenu;
}

void TrayMenu::setModeMenu(QMenu *modeMenu)
{
    m_modeMenu = modeMenu;
}

QAction *TrayMenu::single() const
{
    return m_single;
}

void TrayMenu::setSingle(QAction *single)
{
    m_single = single;
}

QAction *TrayMenu::order() const
{
    return m_order;
}

void TrayMenu::setOrder(QAction *order)
{
    m_order = order;
}

QAction *TrayMenu::rand() const
{
    return m_rand;
}

void TrayMenu::setRand(QAction *rand)
{
    m_rand = rand;
}

QAction *TrayMenu::openLrc() const
{
    return m_openLrc;
}

void TrayMenu::setOpenLrc(QAction *openLrc)
{
    m_openLrc = openLrc;
}

QAction *TrayMenu::lockLrc() const
{
    return m_lockLrc;
}

void TrayMenu::setLockLrc(QAction *lockLrc)
{
    m_lockLrc = lockLrc;
}

QAction *TrayMenu::options() const
{
    return m_options;
}

void TrayMenu::setOptions(QAction *options)
{
    m_options = options;
}

QAction *TrayMenu::exit() const
{
    return m_exit;
}

void TrayMenu::setExit(QAction *exit)
{
    m_exit = exit;
}
