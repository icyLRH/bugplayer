#include "playlistdata.h"
#include "songs.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileInfo>

//name of database
const QString gDatabaseName = "playlist.db";
//name of connetion
const QString gConnectionName = "playlistConnection";

PlayListData::PlayListData(QString name)
{
    setUsername(name);
    //judge whether the database has already been created
    bool isDatabaseExist = QFile::exists(gDatabaseName);
    //if not created
    if (!isDatabaseExist)
    {
        //creat database
        db= QSqlDatabase::addDatabase("QSQLITE", gConnectionName);
        db.setDatabaseName(gDatabaseName);
        db.open();
        //creat songs table
        QSqlQuery sql_query1(db);
        QString create_sql2 =
                QString("create table if not exists %1 (name varchar(30) primary key, duration varchar(30),artist varchar(30), album varchar(30),style varchar(30),place varchar(100));")
                .arg(name);
        //judge whether it is created
        if(!sql_query1.exec(create_sql2))
        {
            qDebug() << "Error: Fail to create table." << sql_query1.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
    }
    //creat database if not exist
    else
    {
        if (QSqlDatabase::contains(gConnectionName))
        {
            db = QSqlDatabase::database(gConnectionName);
            db.open();
            //creat songs table
            QSqlQuery sql_query1(db);
            qDebug()<<11111111111111111;
            QString create_sql2 =
                    QString("create table if not exists %1 (name varchar(30) primary key, duration varchar(30),artist varchar(30), album varchar(30),style varchar(30),place varchar(100));")
                    .arg(name);
            //judge whether the creation is successful
            if(!sql_query1.exec(create_sql2))
            {
                qDebug() << "Error: Fail to create table." << sql_query1.lastError();
            }
            else
            {
                qDebug() << "Table created!";
            }
        }
        else
        {
            db= QSqlDatabase::addDatabase("QSQLITE", gConnectionName);
            db.setDatabaseName(gDatabaseName);
            db.open();
            QSqlQuery sql_query1(db);
            QString create_sql2 =
                    QString("create table if not exists %1 (name varchar(30) primary key,duration varchar(30),artist varchar(30),album varchar(30),style varchar(30),place varchar(100));")
                    .arg(name);
            //judge whether the creation is successful
            if(!sql_query1.exec(create_sql2))
            {
                qDebug() << "Error: Fail to create table." << sql_query1.lastError();
            }
            else
            {
                qDebug() << "Table created!";
            }
        }
    }
}

/*
 * Function Name: insertSong.
 * Description: insert a song's information into the database named by username.
 * Created: 18/09/09
 * Parameter: son Songs
 * Return Code: Bool
 * Author: Icy
*/
bool PlayListData::insertSong(Songs &son)
{
    if (!db.open())
    {
        return false;
    }
    else
    {}
    //whether the song has already exist in the database
    Songs check = selectSongbyplace(son.splace());
    if (check.sname() != NULL)
    {
        //if the song has already exist then insert fail
        qDebug()<<"已存在";
        return false;
    }
    else
    {
        //insertation
        db.open();
        QString sql = QString("insert into %1 (name, duration, artist, album, style,place) ").arg(getUsername());
        sql+=QString("values('%2', '%3', '%4', '%5','%6','%7');")
                .arg(son.sname()).arg(son.sduration()).arg(son.sartist())
                .arg(son.salbum()).arg(son.sstyle()).arg(son.splace());
        QSqlQuery query(db);
        if (!query.exec(sql))
        {
            qDebug() << "insert fail:"
                     << query.lastError().text();
            return false;
        }
        else
        {
            qDebug() << "insert success";
        }
    }
    db.close();
    return true;
}

/*
 * Function Name: deleteSong.
 * Description: delete a song's information by url in the database named by username.
 * Created: 18/09/09
 * Parameter: pl QString
 * Return Code: Bool
 * Author: Icy
*/
bool PlayListData::deleteSong(QString pl)
{
    if (!db.open())
    {
        return false;
    }

    //delete
    QString sql = QString("delete from %1 where place = '%2';").arg(username).arg(pl);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "delete fail:"
                 << query.lastError().text();
        return false;
    }

    db.close();
    return true;
}

/*
 * Function Name: getallSongs.
 * Description: get all song's information in the table to songlist, return the number of songs.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: int
 * Author: Icy
*/
int PlayListData::getallSongs()
{
    int j;
    Songs temp;
    for (j = 0; songlist[j].sname() != "";j++)
    {
        songlist[j] = temp;
    }

    if (!db.open())
    {
        return 0;
    }

    QString sql = QString("select * from %1;").arg(username);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "select fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        songlist[i].setSname(name);
        songlist[i].setSduration(duration);
        songlist[i].setSartist(artist);
        songlist[i].setSalbum(album);
        songlist[i].setSstyle(style);
        songlist[i].setSplace(place);
        i++;
    }

    db.close();
    return i;
}

/*
 * Function Name: selectSongbyplace.
 * Description: get one song's information in the table by url, return the song.
 * Created: 18/09/09
 * Parameter: pl QString
 * Return Code: Songs
 * Author: Icy
*/
Songs PlayListData::selectSongbyplace(QString pl)
{
    Songs so;
    if (!db.open())
    {
        return so;
    }
    //selection
    QString sql = QString("select * from %1 where place = '%2';").arg(username).arg(pl);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return so;
    }

    if(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        so.setSname(name);
        so.setSduration(duration);
        so.setSartist(artist);
        so.setSalbum(album);
        so.setSstyle(style);
        so.setSplace(place);
    }

    db.close();
    return so;
}

/*
 * Function Name: nameofArtists.
 * Description: get all kinds of song's artist name in the table to artistlist, return the number of artists.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: int
 * Author: Icy
*/
int PlayListData::nameofArtists()
{
    int j;
    QString temp = "";
    for (j = 0; artistlist[j] != "";j++)
    {
        artistlist[j] = temp;
    }

    if (!db.open())
    {
        return 0 ;
    }
    //selection
    QString sql = QString("SELECT * FROM %1 WHERE name IN (SELECT MIN(name) FROM songs GROUP BY artist);").arg(username);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        artistlist[i] = query.value(2).toString();
        i++;
    }

    db.close();
    return i;

}

/*
 * Function Name: selectSongbyArtist.
 * Description: get all songs of the artist(ar) to songlist, return the number of songs.
 * Created: 18/09/09
 * Parameter: ar QString
 * Return Code: int
 * Author: Icy
*/
int PlayListData::selectSongbyArtist(QString ar)
{
    int j;
    Songs temp;
    for (j = 0; songlist[j].sname() != "";j++)
    {
        songlist[j] = temp;
    }

    if (!db.open())
    {
        return 0;
    }
    //selection
    QString sql = QString("select * from %1 where artist = '%2';").arg(username).arg(ar);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        songlist[i].setSname(name);
        songlist[i].setSduration(duration);
        songlist[i].setSartist(artist);
        songlist[i].setSalbum(album);
        songlist[i].setSstyle(style);
        songlist[i].setSplace(place);
        i++;
    }

    db.close();
    return i;

}

/*
 * Function Name: nameofStyles.
 * Description: get all kinds of song's style name in the table to stylelist, return the number of styles.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: int
 * Author: Icy
*/
int PlayListData::nameofStyles()
{
    int j;
    QString temp = "";
    for (j = 0; stylelist[j] != "";j++)
    {
        stylelist[j] = temp;
    }

    if (!db.open())
    {
        return 0 ;
    }
    //selection
    QString sql = QString("SELECT * FROM %1 WHERE name IN (SELECT MIN(name) FROM songs GROUP BY style);").arg(username);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        stylelist[i] = query.value(4).toString();
        i++;
    }

    db.close();
    return i;
}

/*
 * Function Name: selectSongbyStyle.
 * Description: get all songs of the style(st) to songlist, return the number of songs.
 * Created: 18/09/09
 * Parameter: st QString
 * Return Code: int
 * Author: Icy
*/
int PlayListData::selectSongbyStyle(QString st)
{
    int j;
    Songs temp;
    for (j = 0; songlist[j].sname() != "";j++)
    {
        songlist[j] = temp;
    }

    if (!db.open())
    {
        return 0;
    }
    //selection
    QString sql = QString("select * from %1 where style = '%2';").arg(username).arg(st);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        songlist[i].setSname(name);
        songlist[i].setSduration(duration);
        songlist[i].setSartist(artist);
        songlist[i].setSalbum(album);
        songlist[i].setSstyle(style);
        songlist[i].setSplace(place);
        i++;
    }

    db.close();
    return i;
}

/*
 * Function Name: orderSong.
 * Description: order all songs by term(name/style/artist) of the table, return the number of songs.
 * Created: 18/09/09
 * Parameter: term QString
 * Return Code: int
 * Author: Icy
*/
int PlayListData::orderSong(QString term)
{
    int j;
    Songs temp;
    for (j = 0; songlist[j].sname() != "";j++)
    {
        songlist[j] = temp;
    }

    if (!db.open())
    {
        return 0;
    }
    //ordering by place, name, artist, album, style
    QString sql = QString("select * from %1 order by %2;").arg(username).arg(term);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "select fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        songlist[i].setSname(name);
        songlist[i].setSduration(duration);
        songlist[i].setSartist(artist);
        songlist[i].setSalbum(album);
        songlist[i].setSstyle(style);
        songlist[i].setSplace(place);
        i++;
    }

    db.close();
    return i;
}

/*
 * Function Name: orderSongbyDesc.
 * Description: order all songs by term(name/style/artist) by inverted order of the table, return the number of songs.
 * Created: 18/09/09
 * Parameter: term QString
 * Return Code: int
 * Author: Icy
*/
int PlayListData::orderSongbyDesc(QString term)
{
    int j;
    Songs temp;
    for (j = 0; songlist[j].sname() != "";j++)
    {
        songlist[j] = temp;
    }

    if (!db.open())
    {
        return 0;
    }
    //inverted ordering by place, name, artist, album, style
    QString sql = QString("select * from %1 order by %2 DESC;").arg(username).arg(term);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "select fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        songlist[i].setSname(name);
        songlist[i].setSduration(duration);
        songlist[i].setSartist(artist);
        songlist[i].setSalbum(album);
        songlist[i].setSstyle(style);
        songlist[i].setSplace(place);
        i++;
    }

    db.close();
    return i;
}

/*
 * Function Name: clear.
 * Description: clear all songs in the table.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Icy
*/
void PlayListData::clear()
{
    db.open();
    QString sql = QString("Delete From %1;").arg(username);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "delete fail:"
                 << query.lastError().text();
    }
}

/*
 * Function Name: searchfromlocal.
 * Description: fuzzy search songs by name/artist/album in the table, write them into songlist.
 * Created: 18/09/09
 * Parameter: se QString
 * Return Code: int
 * Author: Icy
*/
int PlayListData::searchfromlocal(QString se)
{
    int j;
    Songs temp;
    for (j = 0; songlist[j].sname() != "";j++)
    {
        songlist[j] = temp;
    }

    if (!db.open())
    {
        return 0;
    }
    //selection
    QString sql = QString("SELECT * FROM %1 WHERE name LIKE '%%2%' OR artist LIKE '%%2%' OR album LIKE '%%2%';").arg(username).arg(se);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return 0;
    }

    int i = 0;
    while(query.next())
    {
        QString name = query.value(0).toString();
        QString duration = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString style = query.value(4).toString();
        QString place = query.value(5).toString();
        songlist[i].setSname(name);
        songlist[i].setSduration(duration);
        songlist[i].setSartist(artist);
        songlist[i].setSalbum(album);
        songlist[i].setSstyle(style);
        songlist[i].setSplace(place);
        i++;
    }

    db.close();
    return i;
}

QString PlayListData::getUsername() const
{
    return username;
}

void PlayListData::setUsername(const QString &value)
{
    username = value;
}

