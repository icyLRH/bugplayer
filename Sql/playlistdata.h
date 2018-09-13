#ifndef PLAYLISTDATA_H
#define PLAYLISTDATA_H
#include "songs.h"
#include <QString>
#include <QSqlDatabase>
#include <QMediaPlayer>
#include <QStringList>
#include <QString>

class PlayListData
{
public:
    PlayListData(QString name);

    bool insertSong(Songs& son);         // 插入一个歌曲信息到数据表中
    bool deleteSong(QString pl);         //从数据表中删除一个歌曲信息
    int getallSongs();                   //获取播放列表里所有歌
    Songs selectSongbyplace(QString pl);  //在数据表中根据名称查找一个歌曲，并返回这个歌曲
    int nameofArtists();                 //在数据表中查找歌手，返回到artistlist中，函数返回歌手个数
    int selectSongbyArtist(QString ar);  //在数据表中根据歌手查找歌曲，返回到songlist中,函数返回此歌手的歌曲数目
    int nameofStyles();                  //在数据表中查找流派，返回到stylelist中，函数返回流派个数
    int selectSongbyStyle(QString st);   //在数据表中根据流派查找歌曲，返回到songlist中
    int orderSong(QString term);         //（升序）按照term： name, duration, artist, album, style执行排序
                                         //返回到songlist中
    int orderSongbyDesc(QString term);   //（降序）按照term： name, duration, artist, album, style执行排序
                                         //返回到songlist中
    void clear();                        //清除数据库songs表中所有数据
    int searchfromlocal(QString se);     //(搜索前清除重复歌曲）本地数据库中模糊查询(查询歌曲名、歌手、专辑中包含的输入内容），函数返回查询到的个数
                                         //并返回到songlist中

    Songs songlist[100];
    QString artistlist[100];
    QString stylelist[100];

    QString getUsername() const;
    void setUsername(const QString &value);

private:
    QSqlDatabase db;
    QString username;
};

#endif // PLAYLISTDATA_H
