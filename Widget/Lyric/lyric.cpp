#include "lyric.h"

#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QFileInfo>


static int flag = 1;
Lyric::Lyric(QWidget *parent) : QWidget(parent)
{
    //initialize
    lyricLoader = new LyricLoader (this);

    //parentwidget is player
    lyricDialog = new LyricDialog (parentWidget());
    lyricDialog->show();

    //connect
    //get current lrc line
    connect(this,&Lyric::sendCurrentLine,lyricDialog,&LyricDialog::getCurrentLine);
    //lyric change indicated a new start
    connect(lyricLoader,&LyricLoader::lyricChanged,this,&Lyric::startANew);

    //watch flag
    connect(this,&Lyric::flagState,this,&Lyric::flagWatch);
}

    /*
     * Function Name: flagWatch
     * Description: watch flag slot
     * Created: 18/09/09
     * Parameter: state int
     * Return Code: VOID
     * Author: Granx
    */
void Lyric::flagWatch(int state)
{

    //change flag
    flag = state;

    //watch flag
    if(flag == 0)
    {
        lyricDialog->label1->setText("BugPlayer");
    }
}

/*
 * Function Name: startLyric
 * Description: start lyric, open, load lrc
 * Created: 18/09/09
 * Parameter: time qint64
 * Return Code: bool
 * Author: Granx
*/
bool Lyric::startLyric(qint64 time)
{
    totalTime = time;   //save duration
    emit flagState(0);  //close lrc
    if(!openLyric(url))
    {
        return false;
    }

    //attention: process emit signal:lyricChanged，to startANew
    if(!lyricLoader->processContent(qLrc))
    {
        return false;
    }
    emit flagState(1);   //open lrc
    return true;
}


/*
 * Function Name: openLyric
 * Description: open lrc
 * Created: 18/09/09
 * Parameter: url QString
 * Return Code: bool
 * Author: Granx
*/
bool Lyric::openLyric(QString url)
{
    //from web, open ./lyric
    if(url.contains("http", Qt::CaseInsensitive))
    {
        //get music code
        int temp1 = url.lastIndexOf("/");
        QString temp2 = url.right(url.size()-temp1-1);
        qDebug()<<temp2;
        int temp3 = temp2.lastIndexOf(".mp3" );
        QString id = temp2.left(temp3 );
        qDebug()<<id;
        QString urlLrc = "./lyrics/" + id + ".lrc";
        QFile file(urlLrc);

        //open failed
        if(!file.open(QIODevice::ReadOnly))
        {
            return false;
        }
        QTextStream in(&file);
        qLrc = in.readAll();
        qDebug()<<qLrc;
        return true;
    }

    //from local
    else
    {
        QString urlLrc = url.replace(url.right(3),"lrc");
        QFile file(urlLrc);

        //open failed
        if(!file.open(QIODevice::ReadOnly))
        {
           return false;
        }

        QTextStream in(&file);
        qLrc = in.readAll();
        qDebug()<<qLrc;
        return true;
    }
    return true;
}

/*
 * Function Name: startANew
 * Description: reset lastResult
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void Lyric::startANew()
{
    //search from row 0
    lastResult = 0;
}

/*
 * Function Name: getCurrentms
 * Description: get current line text for current ms
 * Created: 18/09/09
 * Parameter: ms qint64
 * Return Code: VOID
 * Author: Granx
*/
void Lyric::getCurrentms(qint64 ms)
{
    //check flag
    if(flag == 0)
    {
        return;
    }
    int result = lyricLoader->getLineByPosition(ms,lastResult);

    //-1 indicates no current lyric
    if(result == -1)
    {
        return;
    }
    else
    {
        //update lastResult,which is next search start line
        lastResult = result;

        //get line for current ms
        currentLine = lyricLoader->mLines.at(result)->text;

        //if next line text exist
        if((result+1) < lyricLoader->mLines.size())
        {
            qint64 time = (lyricLoader->mLines.at(result+1)->time) - ms;
            emit sendCurrentLine(currentLine,time);
        }
        else
        {
            qint64 time = totalTime - ms;
            emit sendCurrentLine(currentLine,time);
        }

    }
}


