#include <QDebug>
#include <QModelIndexList>
#include <QMouseEvent>
#include <newplayer.h>

#include "listtab.h"
#include "player.h"
#include "playlistdata.h"


ListTab::ListTab(QWidget *parent) : DefaultTable(parent),
    m_playlist(new QMediaPlaylist (parent))
{
    //remove actions
    tableMenu()->customRemoveAction(1);
    tableMenu()->customRemoveAction(3);

    //lyric change
    connect(Playlist(), &QMediaPlaylist::currentMediaChanged, static_cast<NewPlayer *>(parentWidget()->parentWidget()), &NewPlayer::startLrc);

    connect(tableMenu(), &TableMenu::flashAction, this, &ListTab::flash);

    //emit Name
    connect(Playlist(), &QMediaPlaylist::currentIndexChanged, this, &ListTab::emitName);
    connect(this, &ListTab::sendIndex, this, &ListTab::emitName);

    //auto selected current index
    connect(Playlist(), &QMediaPlaylist::currentIndexChanged, this, &ListTab::selectRow);
    connect(this, &ListTab::sendIndex, this, &ListTab::selectRow);

    //delete selected music
    connect(this, &ListTab::deleteOver, this, &ListTab::freshAfterDelete);

}

void ListTab::deleteMusic()
{
    //no items selected, return
    if(selectedItems().isEmpty())
    {
        return;
    }

    //all selected songs

    //store all rows index
    QItemSelectionModel *selections = selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap <int, int> rowMap;
    foreach (QModelIndex index, selected)
    {
        rowMap.insert(index.row(), 0);
    }

    //get all row index, emit content
    QMap<int,int>::iterator it;
    for(it = rowMap.begin(); it != rowMap.end(); ++it)
    {
        QList<QTableWidgetItem*>items;
        for(int i = 0; i < columnCount(); i++)
        {
            items<<item(it.key(),i);
        }

        //SQL

        if(!static_cast <Player *>(window())->checkMainWindow()->isloggedin)
        {

            //" guest " is our default account
            PlayListData database("guest");
            database.deleteSong(items.at(items.size() - 1)->data(Qt::DisplayRole).toString());
        }
        else
        {
            PlayListData database(static_cast<Player *>(window())->checkMainWindow()->User());
            database.deleteSong(items.at(items.size() - 1)->data(Qt::DisplayRole).toString());
        }

        //delete from mediaplaylist
        Playlist()->removeMedia(it.key());

        items.clear();
    }



    //inform this to refresh itself
    emit deleteOver();

}

void ListTab::freshAfterDelete()
{
    //clear table
    for(;rowCount()!=0;)
    {
        removeRow(rowCount()-1);
    }

    //database
    PlayListData database(static_cast<Player *>(window())->checkMainWindow()->User());

    //add to table
    int number = database.getallSongs();
    for(int i = 0; i < number; i++)
    {
        addItem(database.songlist[i].getsonglist());
    }

    //check whether playlist is empty or not
    if(Playlist()->mediaCount() == 0)
    {
        return;
    }
    else
    {

    }

    emit sendIndex(Playlist()->currentIndex());
}


/*
 * Function Name: getItems
 * Description: getItems from other places to analyze
 * Created: 18/09/09
 * Parameter: items  const QList<QTableWidgetItem *>
 * Return Code: VOID
 * Author: Granx
*/
void ListTab::getItems(const QList<QTableWidgetItem *> items)
{
    //store all items content
    QStringList list;

    //music url
    QString url;
    for(int i = 0; i < items.size(); i++)
    {
        list<<items.at(i)->data(Qt::DisplayRole).toString();

        //get url
        if(i == items.size() -1)
        {
            url = list.at(i);
        }
    }

    //add to listTab
    addItem(list);

    //add to playList
    //if from web
    if(url.contains("http",Qt::CaseInsensitive))
    {
        Playlist()->addMedia(QUrl(url));
    }

    //else from local
    else
    {
        Playlist()->addMedia(QUrl::fromLocalFile(url));
    }

    //auto change current index
    Playlist()->setCurrentIndex(Playlist()->mediaCount() - 1);

    //SQL
    //check whether cliented or not
    if(!static_cast <Player *>(window())->checkMainWindow()->isloggedin)
    {
        //" guest " is our default account
        PlayListData database("guest");
        Songs song(list);
        database.insertSong(song);
    }
    else
    {
        PlayListData database(static_cast<Player *>(window())->checkMainWindow()->User());
        Songs song(list);
        database.insertSong(song);
    }

}

/*
 * Function Name: flash
 * Description: refresh information from database
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void ListTab::flash()
{

    //first, clear playList
    if(!Playlist()->clear())
    {
        return;
    }

    //clear table
    for(;rowCount()!=0;)
    {
        removeRow(rowCount()-1);
    }   

    //database
    PlayListData database(static_cast<Player *>(window())->checkMainWindow()->User());

    //add to table
    int number = database.getallSongs();
    for(int i = 0; i < number; i++)
    {
        addItem(database.songlist[i].getsonglist());

        //add to playList
        QString url = database.songlist[i].getsonglist().at(5);
        if(url.contains("http"))
        {
            Playlist()->addMedia(QUrl(url));
        }
        else
        {
            Playlist()->addMedia(QUrl::fromLocalFile(url));
        }

    }


    //check whether playlist is empty or not
    if(Playlist()->mediaCount() == 0)
    {
        return;
    }
    else
    {
        Playlist()->setCurrentIndex(0);
    }

    //inform newplay to play
    emit flashOver();
}

/*
 * Function Name: emitName
 * Description: emit name and artist for horse label, tray tooltip.
 * Created: 18/09/09
 * Parameter: index int
 * Return Code: VOID
 * Author: Granx
*/
void ListTab::emitName(int index)
{
    emit nameAndArtist(this->item(index,0)->data(Qt::DisplayRole).toString(),this->item(index,2)->data(Qt::DisplayRole).toString());
}



QMediaPlaylist *ListTab::Playlist() const
{
    return m_playlist;
}

void ListTab::setPlaylist(QMediaPlaylist *playlist)
{
    m_playlist = playlist;
}


/*
 * Function Name: mouseDoubleClickEvent
 * Description: override mouseDoubleClickEvent to achieve play selected music.
 * Created: 18/09/09
 * Parameter: event QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void ListTab::mouseDoubleClickEvent(QMouseEvent *event)
{
    QList<QTableWidgetItem *> Items =selectedItems();

    //check
    if(Items.size()!= 6)
    {
        return;
    }

    QTableWidgetItem *urlItem;
    urlItem = Items.at(Items.size()-1);

    QString url = urlItem->data(Qt::DisplayRole).toString();

    Playlist()->setCurrentIndex(currentRow());

    //inform newplayer
    emit sendUrl(url);

    event->accept();

}




