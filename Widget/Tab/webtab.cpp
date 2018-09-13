#include "webtab.h"
#include "lyricdownload.h"

#include <QStringList>
#include <QString>


static int j = 0;
static int i = 0;//静态全局变量，用于循环

//宏定义，最基本的api字段
#define  MP3_URL                 "http://tingapi.ting.baidu.com/v1/restserver/ting?"

//http处理对象声明
QNetworkAccessManager *network_manager2 = new QNetworkAccessManager();
QNetworkRequest *network_request2 = new QNetworkRequest();

WebTab::WebTab(QWidget *parent) : DefaultTable(parent)
{

    tableMenu()->customRemoveAction(2);
    tableMenu()->customRemoveAction(3);
    tableMenu()->customRemoveAction(4);

    //本类接收network传来的songid,再一次向网页发送请求获取歌曲url链接和歌词链接
    //李雨峤 2015/9/7
    connect(this,
            &WebTab::getListOk,
            this,
            &WebTab::getSongList);
    connect(this,
            &WebTab::getUrlOk,
            this,
            &WebTab::startAddItems);
    connect(this,
            &WebTab::getAUrlOk,
            this,
            &WebTab::getSongList);//zh
}

/*
 * Function Name:dealStringlist
 * Description:处理歌曲和专辑名中的特殊字段 如:<em>周杰伦</em>
 * Created:  2015/9/7
 * Parameter: QStringList &list
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::dealStringlist(QStringList &list)
{

    for(int i=0;i<list.size();i++)
    {
        QString str = list.at(i);
        str = str.replace("<em>","");
        str=str.replace("</em>","");
        list.replace(i,str);
    }
}

/*
 * Function Name:transfer
 * Description:处理歌曲和专辑名中的特殊字段 如:<em>周杰伦</em>
 * Created:  2015/9/7
 * Parameter: QString url
 * Return Code: QString
 * Author: 李雨峤
*/
QString WebTab::transfer(QString url)
{

            int temp1 = url.lastIndexOf("/");
            QString temp2 = url.right(url.size()-temp1-1);
            qDebug()<<temp2;
            int temp3 = temp2.lastIndexOf(".mp3" );
            QString id = temp2.left(temp3 );
            return id;

}


/*
 * Function Name:getList
 * Description:处理歌曲和专辑名中的特殊字段 如:<em>周杰伦</em>
 * Created:  2015/9/7
 * Parameter: QStringList name,
              QStringList lenth,
              QStringList artist,
              QStringList album,
              QStringList id
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::getList(QStringList name,
                     QStringList lenth,
                     QStringList artist,
                     QStringList album,
                     QStringList id)
{

    namelist = name;
    lengthlist = lenth;
    artistlist = artist;
    albumlist = album;
    songidlist = id;

    dealStringlist(namelist);
    dealStringlist(artistlist);
    dealStringlist(albumlist);

    //表示list已设置好，进行下一步
    emit getListOk();
}

/*
 * Function Name:getSongList
 * Description:getListOk和getAUrlOk的槽函数，获取第j个歌曲的url
 * Created:  2015/9/7
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::getSongList()
{
     gainSongUrl(songidlist.at(j));
     j++;

}

/*
 * Function Name:gainSongUrl
 * Description:通过歌曲id向api接口网页发送请求
 * Created:  2015/9/7
 * Parameter: QString song_id
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::gainSongUrl(QString song_id)
{

    //设置发送的数据
    QByteArray byte_array;
    byte_array.append("method=baidu.ting.song.play");
    byte_array.append("&format=xml");

    byte_array.append("&songid=" + song_id);  //text指歌曲名称、歌手名称
    QString url = MP3_URL + QString(byte_array);
    //qDebug()<<url;

    connect(network_manager2,
            &QNetworkAccessManager::finished,
            this,
            &WebTab::sidReplyFinished);

    network_request2->setUrl(QUrl(url));
    network_manager2->get(*network_request2);

}

/*
 * Function Name:sidReplyFinished
 * Description:通过歌曲id向api接口网页发送请求
 * Created:  2015/9/7
 * Parameter: QNetworkReply *reply
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::sidReplyFinished(QNetworkReply *reply)
{
        QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug()<<"第二次状态码（200正常）:"<<status_code;
        //无错误返回
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray bytes = reply->readAll();  //获取字节
            QString result(bytes);  //转化为字符串


    parseJson(result);//自定义方法，解析json文件，具体见声明

        }
        else
        {
            qDebug()<<"WRONG!";//获取失败
        }
}


/*
 * Function Name:startAddItems
 * Description:已获取到一首歌曲的全部必要信息，整合为item，加入到列表当中
 * Created:  2015/9/7
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::startAddItems()
{


    emit sendLyric(lyrlinklist,codelist);
    qDebug()<<"传一次了哟";
    for(int j = 0; j < namelist.size(); j++)
    {

            QStringList item;
            item<<namelist.at(j)
                <<lengthlist.at(j)
                <<artistlist.at(j)
                <<albumlist.at(j)
                <<""
                <<songurllist.at(j);
            addItem(item);


    }
    //结束后清空list

    songidlist.clear();
    namelist.clear();
    artistlist.clear();
    albumlist.clear();
    songurllist.clear();
    lengthlist.clear();
    lyrlinklist.clear();
    codelist.clear();
}

/*
 * Function Name:parseJson
 * Description:解析网页返回的json文件
 * Created:  2015/9/7
 * Parameter: QString json
 * Return Code: VOID
 * Author: 李雨峤
*/
void WebTab::parseJson(QString json)
{


    QByteArray byte_array;
    QJsonParseError json_error;
    QString str = "";//歌曲url
    int time = 0;//歌曲时长
    QString lyr = "";//歌词链接
    QString code = "";//歌词文件编号

    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        //检测根目录是否为object
       if(parse_doucment.isObject())
       {
           QJsonObject obj = parse_doucment.object();

           // 遍历标签内的值，寻求关键字
           time =getTimeBykey(obj,
                              "file_duration");//查询时长标签

           //将时长转化为分：秒格式
           int minute = time/60;
           int seconds = time % 60;
           QString strtime=tr("%1:%2").arg(minute).arg(seconds,2,10,QLatin1Char('0'));

           str = getValueBykey(obj,
                               "show_link");//查询url标签
           code = transfer(str);//获取url里的歌词文件编号
           lyr = getLrcBykey(obj,
                             "lrclink");//获取歌词链接标签

           //将获取到的信息加载到list当中
           lengthlist<<strtime;
           songurllist<<str;
           lyrlinklist<<lyr;
           codelist<<code;

           qDebug()<<"str: "<<str;

           qDebug()<<"time: "<<strtime;

           qDebug()<<"lyr: "<<lyr;


           i++;

           if(songurllist.size()==namelist.size())
           {
               //如果加载完毕，发送完毕信号
               i = 0;
               j = 0;
                 emit getUrlOk();
           }
           else
           {
               //继续加载
               emit getAUrlOk(); //zh
           }


       }
    }

}

/*
 * Function Name:getValueBykey
 * Description:用于获取key关键字内的信息，适合object嵌套的json文件
 * Created:  2015/9/7
 * Parameter: QJsonObject obj,
              QString key
 * Return Code: QString
 * Author: 李雨峤
*/
QString WebTab::getValueBykey(QJsonObject obj,
                              QString key)
{


    QString rst = "";

        QStringList strList = obj.keys();

         for (int i = 0; i < obj.size()-1; i++)

         {

             QJsonValue val = obj.value(strList.at(i));


             if ( strList.at(i) == key && val.isString())

             {
                 //是当前关键字标签，则获取里面的值

                 rst = val.toString();

             }

             else if (val.isObject())

             {

                 //进入到内层object，继续寻找
                 rst = getValueBykey(val.toObject(), key);//递归调用

             }

         }
    return rst;//返回取得结果
}

/*
 * Function Name:getTimeBykey
 * Description:用于获取key关键字内的信息，适合object嵌套的json文件
 * Created:  2015/9/7
 * Parameter: QJsonObject obj,
              QString key
 * Return Code: QString
 * Author: 李雨峤
*/
double WebTab::getTimeBykey(QJsonObject obj,
                            QString key)
{


    double rst = 0.0;

        QStringList strList = obj.keys();

         for (int i = 0; i < obj.size()-1; i++)

         {
             QJsonValue val = obj.value(strList.at(i));

             if ( strList.at(i) == key && val.isDouble())

             {

                 rst = val.toDouble();


             }

             else if (val.isObject())

             {

                 rst = getTimeBykey(val.toObject(),
                                    key);

             }

         }
    return rst;
}

/*
 * Function Name:getLrcBykey
 * Description:用于获取key关键字内的信息，适合object嵌套的json文件
 * Created:  2015/9/7
 * Parameter: QJsonObject obj,
              QString key
 * Return Code: QString
 * Author: 李雨峤
*/
QString WebTab::getLrcBykey(QJsonObject obj,
                            QString key)
{


    QString rst = "";

        QStringList strList = obj.keys();


         for (int i = 0; i < obj.size(); i++)

         {

             QJsonValue val = obj.value(strList.at(i));


             if ( strList.at(i) == key && val.isString())

             {

                 rst = val.toString();

             }

             else if (val.isObject())

             {

                 rst = getValueBykey(val.toObject(),
                                     key);

             }

         }
    return rst;
}
