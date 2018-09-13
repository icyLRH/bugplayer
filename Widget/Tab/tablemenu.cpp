#include "tablemenu.h"

#include <QDebug>


TableMenu::TableMenu(QWidget *parent) : QMenu(parent),
    m_addToListTab(new QAction (QIcon(":/image/src/middlewidget/btn_islove (3).png"),"添加到播放列表",this)),
    m_flash(new QAction (QIcon(":/image/src/middlewidget/btn_addtips (2).png"),"删除重复歌曲",this)),
    m_deleteMusic(new QAction (QIcon(":/image/src/middlewidget/btn_del (2).png"),"删除所选歌曲",this)),
    m_addToDefaultTab(new QAction (QIcon(":/image/src/middlewidget/btn_cross (2).png"),"添加歌曲",this))
{
    //addAction
    addAction(addToListTab());  
    addAction(deleteMusic());
    addAction(addToDefaultTab());
    addAction(flash());

    //connect actions, emit
    connect(addToListTab(),&QAction::triggered,this,&TableMenu::emitAddToListTab);
    connect(flash(),&QAction::triggered,this,&TableMenu::emitFlash);
    connect(deleteMusic(),&QAction::triggered,this,&TableMenu::emitDeleteMusic);
    connect(addToDefaultTab(),&QAction::triggered,this,&TableMenu::emitAddToDefaultTab);

    customStylesSheet();
}

/*
 * Function Name: customStylesSheet
 * Description: set styles sheet
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void TableMenu::customStylesSheet()
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
                  "QMenu::sperator{height:1px;"
                  "background-color:rgba(220,220,220,200);}");
}

/*
 * Function Name: customRemoveAction
 * Description: remove certain index action
 * Created: 18/09/09
 * Parameter: index int
 * Return Code: VOID
 * Author: Granx
*/
void TableMenu::customRemoveAction(int index)
{
    switch (index) {
    case 1:
        removeAction(addToListTab());
        break;
    case 2:
        removeAction(deleteMusic());
        break;
    case 3:
        removeAction(addToDefaultTab());
        break;
    case 4:
        removeAction(flash());
        break;
    default:
        break;
    }
}

QAction *TableMenu::addToListTab() const
{
    return m_addToListTab;
}

void TableMenu::setAddToListTab(QAction *addToListTab)
{
    m_addToListTab = addToListTab;
}

void TableMenu::emitAddToListTab()
{
    emit addToListTabAction();
}

void TableMenu::emitFlash()
{
    emit flashAction();
}

void TableMenu::emitDeleteMusic()
{
    emit deleteMusicAction();
}

void TableMenu::emitAddToDefaultTab()
{
    emit addToDefaultTabAction();
}

QAction *TableMenu::addToDefaultTab() const
{
    return m_addToDefaultTab;
}

void TableMenu::setAddToDefaultTab(QAction *addToDefaultTab)
{
    m_addToDefaultTab = addToDefaultTab;
}

QAction *TableMenu::deleteMusic() const
{
    return m_deleteMusic;
}

void TableMenu::setDeleteMusic(QAction *deleteMusic)
{
    m_deleteMusic = deleteMusic;
}

QAction *TableMenu::flash() const
{
    return m_flash;
}

void TableMenu::setFlash(QAction *flash)
{
    m_flash = flash;
}

