#include "playtab.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <songsdata.h>
#include <QFontDatabase>

PlayTab::PlayTab(QWidget *parent) : QTabWidget(parent),
    m_defaultTab(new DefaultTab (this)),
    m_artistTab(new ArtistTab (this)),
    m_genreTab(new GenreTab (this)),
    m_webTab(new WebTab (this)),
    m_listTab(new ListTab (this)),
    m_lastIndex(-1)
{
    //set custom tabBar
    NewTabBarOfPlayTab *newTabBar = new NewTabBarOfPlayTab (this);
    setTabBar(newTabBar);

    // accept drops to auto change to default tab
    setAcceptDrops(true);

    //allow move
    tabBar()->setMovable(true);

    addTab(defaultTab(),QIcon(":/image/src/category/song.png"),"歌曲");
    addTab(artistTab(),QIcon(":/image/src/category/artist.png"),"艺术家");
    addTab(genreTab(),QIcon(":/image/src/category/genre.png"),"流派");
    addTab(webTab(),QIcon(":/image/src/category/store.png"),"网络");
    addTab(listTab(),QIcon(":/image/src/category/playlist.png"),"播放列表");

    //connect fresh
    connect(defaultTab(),&DefaultTab::fresh,this,&PlayTab::fresh);

    //connect delete over to defaultTable, which will inform this to refresh other tabs
    //connection of artistTab, genreTab are in this->fresh, which is s slot of signal in defaultTab
    connect(defaultTab(),&DefaultTab::deleteOver,defaultTab(),&DefaultTab::flash);


    //connect defaultTab, listTab
    connect(defaultTab(),&DefaultTab::sendItems,listTab(),&ListTab::getItems);
    connect(webTab(),&WebTab::sendItems,listTab(),&ListTab::getItems);

    setStyleSheet("border: 0px;");
    setIconSize(QSize(40,40));
    connect(this,&PlayTab::currentChanged,this,&PlayTab::changeIconFont);

}



/*
 * Function Name: fresh
 * Description: get signal from tabs and refresh
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::fresh()
{
    // SQL
    SongsData songsData;

    //fresh artistTab
    artistTab()->clear();

    //re add
    for(int i = 0; i < songsData.nameofArtists();i++)
    {
        QString artist = songsData.artistlist[i];
        m_table = artistTab()->addTab_(artist);

        int number = songsData.selectSongbyArtist(artist);
        for(int j = 0; j < number; j++)
        {
            table()->addItem(songsData.songlist[j].getsonglist());
        }

        connect(table(),&DefaultTable::sendItems,listTab(),&ListTab::getItems);

        //connect deleteover and flash
        connect(table(),&DefaultTable::deleteOver,defaultTab(),&DefaultTab::flash);
        //connect tablemenu add
        connect(table()->tableMenu(),&TableMenu::addToDefaultTabAction,defaultTab(),&DefaultTab::select);

        //inform newplayer to add connect table and mediaplayer
        emit freshOver();

    }

    //fresh genreTab
    genreTab()->clear();

    //re add
    for(int i = 0; i < songsData.nameofStyles();i++)
    {
        QString genre = songsData.stylelist[i];
        m_table = genreTab()->addTab_(genre);
        int number = songsData.selectSongbyStyle(genre);
        for(int j = 0; j < number; j++)
        {
            table()->addItem(songsData.songlist[j].getsonglist());
        }

        connect(table(),&DefaultTable::sendItems,listTab(),&ListTab::getItems);

        //connect deleteover and flash
        connect(table(),&DefaultTable::deleteOver,defaultTab(),&DefaultTab::flash);
        //connect tablemenu add
        connect(table()->tableMenu(),&TableMenu::addToDefaultTabAction,defaultTab(),&DefaultTab::select);

        //inform newplay to add connect table and mediaplayer
        emit freshOver();

    }

}

/*
 * Function Name: getLogin
 * Description: auto change index of playTab
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::getLogin()
{
    setCurrentIndex(indexOf(listTab()));
}


/*
 * Function Name: changeIconFont
 * Description: change
 * Created: 18/09/09
 * Parameter: index int
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::changeIconFont(int index)
{

    //Icon
    if(index == indexOf(artistTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/artist1.png"));
    }
    else if (index == indexOf(defaultTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/song1.png"));
    }
    else if (index == indexOf(genreTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/genre1.png"));
    }
    else if (index == indexOf(webTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/store1.png"));
    }
    else if (index == indexOf(listTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/playlist1.png"));
    }
    else
    {

    }


    //reset icon, font
    if(m_lastIndex != -1)
    {
        resetIconFont(m_lastIndex);
    }
    m_lastIndex = index;
}

/*
 * Function Name: resetIconFont
 * Description: reset
 * Created: 18/09/09
 * Parameter: index int
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::resetIconFont(int index)
{
    if(index == indexOf(artistTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/artist.png"));
    }
    else if (index == indexOf(defaultTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/song.png"));
    }
    else if (index == indexOf(genreTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/genre.png"));
    }
    else if (index == indexOf(webTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/store.png"));
    }
    else if (index == indexOf(listTab()))
    {
        setTabIcon(index,QIcon(":/image/src/category/playlist.png"));
    }
    else
    {

    }
}

int PlayTab::getLastIndex() const
{
    return m_lastIndex;
}

void PlayTab::setLastIndex(int lastIndex)
{
    m_lastIndex = lastIndex;
}



ListTab *PlayTab::listTab() const
{
    return m_listTab;
}

void PlayTab::setListTab(ListTab *listTab)
{
    m_listTab = listTab;
}

/*
 * Function Name: webSearched
 * Description: auto clear webTab, change index
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::webSearched()
{
    //clear
    for(;webTab()->rowCount()!=0;)
    {
        webTab()->removeRow( webTab()->rowCount()-1);
    }


    setCurrentIndex(indexOf(webTab()));

}

/*
 * Function Name: localSearched
 * Description: auto  change index, achieve local search
 * Created: 18/09/09
 * Parameter: text  QString
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::localSearched(QString text)
{
    setCurrentIndex(indexOf(defaultTab()));

    QTableWidget *source = defaultTab();
    //

    //         1、判断输入是否为空？全部显示（结束）：进一步判断

    //         2、获取符合条件的行号

    //         3、隐藏所有行

    //         4、判断行号是否为空？（结束操作）：显示相关行（结束）

    //get line
    int rC = source->rowCount();

    //check text is empty or not
    if ("" == text)
    {
        for (int i = 0; i < rC; i++)
        {
            //show all rows
            source->setRowHidden(i, false);
        }
    }
    else
    {
        //get corresponding item
        QList <QTableWidgetItem *> item = source->findItems(text, Qt::MatchContains);

        for (int i = 0; i < rC; i++)
        {
            //hide all row
            source->setRowHidden(i, true);

        }

        if (!item.isEmpty())
        {
            for (int i = 0; i < item.count(); i++)
            {
                source->setRowHidden(item.at(i)->row(), false);
            }
        }
    }




}

/*
 * Function Name: dragEnterEvent
 * Description: auto  change index
 * Created: 18/09/09
 * Parameter: event  QDragEnterEvent *
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::dragEnterEvent(QDragEnterEvent *event)
{
    setCurrentIndex(indexOf(defaultTab()));     //目的：自动定位到默认列表
    event->accept();
}

WebTab *PlayTab::webTab() const
{
    return m_webTab;
}

void PlayTab::setWebTab(WebTab *webTab)
{
    m_webTab = webTab;
}

/*
 * Function Name: resizeEvent
 * Description: override resizeEvent for NewTabBar to auto change width
 * Created: 18/09/09
 * Parameter: event  QResizeEvent *
 * Return Code: VOID
 * Author: Granx
*/
void PlayTab::resizeEvent(QResizeEvent *event)
{
    emit resizeEventHappened();
    QTabWidget::resizeEvent(event);
}

QWidget *PlayTab::lrcTab() const
{
    return m_lrcTab;
}

void PlayTab::setLrcTab(QWidget *lrcTab)
{
    m_lrcTab = lrcTab;
}

DefaultTab *PlayTab::defaultTab() const
{
    return m_defaultTab;
}

void PlayTab::setDefaultTab(DefaultTab *defaultTab)
{
    m_defaultTab = defaultTab;
}

ArtistTab *PlayTab::artistTab() const
{
    return m_artistTab;
}

void PlayTab::setArtistTab(ArtistTab *artistTab)
{
    m_artistTab = artistTab;
}

GenreTab *PlayTab::genreTab() const
{
    return m_genreTab;
}

void PlayTab::setGenreTab(GenreTab *genreTab)
{
    m_genreTab = genreTab;
}


DefaultTable *PlayTab::table() const
{
    return m_table;
}

void PlayTab::setTable(DefaultTable *table)
{
    m_table = table;
}




