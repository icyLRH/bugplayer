#include <QStringList>
#include <QAbstractItemView>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QUrl>
#include <QFile>
#include <QMimeData>
#include <QFileDialog>
#include <QDirIterator>

#include <taglib.h>
#include <fileref.h>
#include <tag.h>
#include <tstring.h>
#include <tpropertymap.h>

#include "defaulttab.h"
#include "songs.h"
#include "songsdata.h"


DefaultTab::DefaultTab(QWidget *parent) : DefaultTable(parent)
{
    //acceptdrops
    setAcceptDrops(true);

    //connect tableMenu
    connect(tableMenu(),&TableMenu::flashAction,this,&DefaultTab::flash);
    connect(tableMenu(),&TableMenu::addToDefaultTabAction,this,&DefaultTab::select);
}

/*
 * Function Name: flash
 * Description: clear and refresh the table by database, emit a signal to inform playTab to refresh.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTab::flash()
{
    //clear table
    for(;rowCount() != 0;)
    {
        removeRow(rowCount() - 1);
    }

    //database ready
    SongsData songsData;

    //addItem
    int number = songsData.getallSongs();
    for(int i = 0; i < number; i++)
    {
        addItem(songsData.songlist[i].getsonglist());
    }

    //purpose: inform playTab to refresh
    emit fresh();
}

/*
 * Function Name: select
 * Description: select by QFileDialog to add mp3 music, get infomation, inform playTab to refresh.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTab::select()
{
    //create QFileDialog pointer
    QFileDialog *fileDialog = new QFileDialog(this);

    //title
    fileDialog->setWindowTitle(tr("打开音乐"));

    //default dir
    fileDialog->setDirectory(".");

    //filter
    fileDialog->setNameFilter(tr("MP3 Music(*.mp3)"));

    //fileMode
    fileDialog->setFileMode(QFileDialog::ExistingFiles);

    //viewMode
    fileDialog->setViewMode(QFileDialog::Detail);

    //store the url
    QStringList urlList;
    if(fileDialog->exec())
    {
        urlList = fileDialog->selectedFiles();
    }

    for(int i = 0; i < urlList.size(); i++)
    {
        //get media information

        //string conversion
        QString qFileName = urlList.at(i);
        std::wstring wFileName = qFileName.toStdWString();
        TagLib::FileName name (wFileName.c_str());

        TagLib::FileRef file(name, true, TagLib::AudioProperties::Average);

        TagLib::Tag *tag = file.tag();

        //title
        TagLib::String tTitle = tag->title();

        //artist
        TagLib::String tArtist = tag->artist();

        //album
        TagLib::String tAlbum = tag->album();

        //genre
        TagLib::String tGenre = tag->genre();

        //string conversion
        QString qTitle = QString::fromStdWString(tTitle.toWString());
        QString qArtist = QString::fromStdWString(tArtist.toWString());
        QString qAlbum = QString::fromStdWString(tAlbum.toWString());
        QString qGenre = QString ::fromStdWString(tGenre.toWString());

        //calculate duration/time
        TagLib::AudioProperties *properties = file.audioProperties();
        int seconds = properties->length() % 60;
        int minutes = properties->length() / 60;
        QString qTime = QString("%1:%2").arg(minutes).arg(seconds,2,10,QLatin1Char('0'));

        QStringList stringList = {qTitle,qTime,qArtist,qAlbum,qGenre,qFileName};

        //add to table
        addItem(stringList);

        //add to database
        Songs song(qTitle,qTime,qArtist,qAlbum,qGenre,qFileName);
        SongsData songsData;
        songsData.insertSong(song);

    }

    //inform playTab to refresh
    emit fresh();
}

/*
 * Function Name: scan
 * Description: scan path to add mp3 music, get infomation, inform playTab to refresh.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTab::scan()
{
    //set fileName
    QString filename("*.mp3");

    //get Path for scan by QFileDialog
    QString strFilePath = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("选择路径"),QDir::currentPath()));

    //store corresponding url
    QStringList urlList;
    if (strFilePath.isEmpty() || filename.isEmpty())
    {
        return ;
    }
    QDir dir;
    QStringList filters;

    //insert fileName into filters
    filters << filename;

    //set path and filters, dir
    dir.setPath(strFilePath);
    dir.setNameFilters(filters);

    //QDirIterator traverse all the dir with recusion
    QDirIterator iter(dir,QDirIterator::Subdirectories);

    //start
    while (iter.hasNext())
    {
        iter.next();
        QFileInfo info=iter.fileInfo();
        if (info.isFile())
        {
            urlList.append(info.absoluteFilePath());
        }
    }

    //get media infomation
    for(int i = 0; i < urlList.size(); i++)
    {
        QString qFileName = urlList.at(i);
        std::wstring wFileName = qFileName.toStdWString();
        TagLib::FileName name (wFileName.c_str());

        TagLib::FileRef file(name,true,TagLib::AudioProperties::Average);

        TagLib::Tag *tag = file.tag();

        //title
        TagLib::String tTitle = tag->title();

        //artist
        TagLib::String tArtist = tag->artist();

        //album
        TagLib::String tAlbum = tag->album();

        //genre
        TagLib::String tGenre = tag->genre();

        //string conversion
        QString qTitle = QString::fromStdWString(tTitle.toWString());
        QString qArtist = QString::fromStdWString(tArtist.toWString());
        QString qAlbum = QString::fromStdWString(tAlbum.toWString());
        QString qGenre = QString ::fromStdWString(tGenre.toWString());


        //calculate duration/time
        TagLib::AudioProperties *properties = file.audioProperties();
        int seconds = properties->length() % 60;
        int minutes = properties->length() / 60;
        QString qTime = QString("%1:%2").arg(minutes).arg(seconds,2,10,QLatin1Char('0'));

        QStringList stringList = {qTitle,qTime,qArtist,qAlbum,qGenre,qFileName};

        //add to table
        addItem(stringList);

        //add to database
        Songs song(qTitle,qTime,qArtist,qAlbum,qGenre,qFileName);
        SongsData songsData;
        songsData.insertSong(song);

    }

    //inform playTab to refresh
    emit fresh();

}

/*
 * Function Name: dragEnterEvent
 * Description: judge the files can accept or not
 * Created: 18/09/09
 * Parameter: event QDragEnterEvent*
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTab::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData* mimeData = event->mimeData();

    //read information
    if(mimeData->hasUrls())
    {

        //dispose every url
        for(int i = 0; i < mimeData->urls().size(); i++)
        {
            //get name suffix
            QString suffix = mimeData->urls()[0].fileName().right(3);

            ////now, it is only supposed to accept *.mp3
            //compare, when equals, return 0
            if(suffix.compare("mp3",Qt::CaseInsensitive)<0)
            {

                //if a file's suffix is not mp3, do not accept at all
                event->ignore();
                return;
            }
        }

        //if don't return, indicate all are *.mp3, acceptProposedAction
        event->acceptProposedAction();
    }

    //else, there is no urls
    else
    {
        event->ignore();
    }

}

/*
 * Function Name: dropEvent
 * Description: accept dragEvent to add mp3 music, get infomation, inform playTab to refresh.
 * Created: 18/09/09
 * Parameter: event QDropEvent*
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTab::dropEvent(QDropEvent *event)
{
    qDebug()<<"getting mime data";

    //mimeData
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls())
    {
        QList<QUrl>urlList = mimeData->urls();

        //dispose
        for(int i = 0; i < mimeData->urls().size();i++)
        {
            //conversion
            std::wstring wFileName = urlList.at(i).toLocalFile().toStdWString();
            QString qFileName = QString::fromStdWString(wFileName);

            TagLib::FileName name (wFileName.c_str());

            TagLib::FileRef file(name,true,TagLib::AudioProperties::Average);

            TagLib::Tag *tag = file.tag();

            TagLib::String tTitle = tag->title();

            TagLib::String tArtist = tag->artist();

            TagLib::String tAlbum = tag->album();

            TagLib::String tGenre = tag->genre();

            //convertion
            QString qTitle = QString::fromStdWString(tTitle.toWString());
            QString qArtist = QString::fromStdWString(tArtist.toWString());
            QString qAlbum = QString::fromStdWString(tAlbum.toWString());
            QString qGenre = QString ::fromStdWString(tGenre.toWString());

            TagLib::AudioProperties *properties = file.audioProperties();
            int seconds = properties->length() % 60;
            int minutes = properties->length() / 60;
            QString qTime = QString("%1:%2").arg(minutes).arg(seconds,2,10,QLatin1Char('0'));

            QStringList stringList = {qTitle,qTime,qArtist,qAlbum,qGenre,qFileName};

            //addItem to table
            addItem(stringList);

            //add to database
            Songs song(qTitle,qTime,qArtist,qAlbum,qGenre,qFileName);
            SongsData songsData;
            songsData.insertSong(song);

        }

    }

    //inform playTab to fresh
    emit fresh();

}

/*
 * Function Name: dragMoveEvent
 * Description: accept dragEvent.
 * Created: 18/09/09
 * Parameter: event QDragMoveEvent*
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTab::dragMoveEvent(QDragMoveEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}



