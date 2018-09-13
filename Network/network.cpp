#include "network.h"

#define  MP3_URL                 "http://tingapi.ting.baidu.com/v1/restserver/ting?"

QNetworkAccessManager *network_manager;
QNetworkRequest *network_request;

Network::Network(QWidget *parent) : QWidget(parent)
{
    //本类通过API向网页发送请求，获取20首歌曲的名称，作者，专辑名，歌曲ID
}

/*
 * Function Name:searchReceived
 * Description: 槽函数，当点击搜索按键后，向http发送请求
 * Created: 2015/9/5
 * Parameter: QString text
 * Return Code: VOID
 * Author: 李雨峤
*/
void Network::searchReceived(QString text)
{


    //设置发送的数据
    qDebug()<<"text: "<<text;
    QByteArray byte_array;

    //将请求字段加入bytearray数组
    byte_array.append("method=baidu.ting.search.common");

    byte_array.append("&query=" + text);  //text指歌曲名称、歌手名称
    byte_array.append("&page_size=20");
    byte_array.append("&page_no=1");
    byte_array.append("&format=xml");
    QString url = MP3_URL + QString(byte_array);
    qDebug()<<url;

    network_manager = new QNetworkAccessManager();
    network_request = new QNetworkRequest();

    connect(network_manager,
            &QNetworkAccessManager::finished,
            this,
            &Network::replyFinished);

    //发送请求
    network_request->setUrl(QUrl(url));

    //接收网页返回结果
    network_manager->get(*network_request);

}

/*
 * Function Name:replyFinished
 * Description: 槽函数，获取响应的信息并处理，状态码为200表示正常
 * Created: 2015/9/5
 * Parameter: QNetworkReply *reply
 * Return Code: VOID
 * Author: 李雨峤
*/
void Network::replyFinished(QNetworkReply *reply)
{


        QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug()<<"状态码（200正常）:"<<status_code;

        //无错误返回
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray bytes = reply->readAll();

            //获取字节,转化为字符串
            QString result(bytes);


            parseXml(result);//解析xml,详细过程见声明

            qDebug()<<songidlist;

        }
        else
        {
            qDebug()<<"WRONG!";
        }
}


/*
 * Function Name:parseXml
 * Description: 解析返回的xml文件
 * Created: 2015/9/5
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void Network::parseXml(QString xml)
{


    QDomDocument doc;


    doc.setContent(xml);
    QDomElement root = doc.documentElement();


            //设置根节点
            QDomNode node = root.firstChild();

            //遍历xml，寻找关键字
            while(!node.isNull())
            {

                QDomElement element = node.toElement(); // 将节点转为元素处理
                if(element.tagName()=="song_list")
                {
                QDomNode node2 = element.firstChild();//进入song....song.....song....子节点

                          while(!node2.isNull())
                          {

                              QDomElement element2 = node2.toElement();
                              if(!element2.isNull())
                              {
                                 //进入二级子节点
                                  QDomNode nodeson = element2.firstChild();
                                  while(!nodeson.isNull())
                                  {
                                      QDomElement elementson = nodeson.toElement();

                                      if(!elementson.isNull())
                                      {

                                  //已寻找到关键字节点，提取关键字
                                  if (elementson.tagName()=="title")
                                  {
                                      setStrname(elementson.text());
                                      namelist<<elementson.text();
                                  }
                                  else if (elementson.tagName()=="song_id") {
                                      setStrsongid(elementson.text());
                                      songidlist<<elementson.text();
                                      qDebug()<<"songid:"<<elementson.text();

                                  }
                                  else if (elementson.tagName()=="author") {
                                     setStrartist(elementson.text());
                                     artistlist<<elementson.text();
                                  }
                                  else if (elementson.tagName()=="album_title") {
                                     setStralbum(elementson.text());
                                     albumlist<<elementson.text();
                                  }
                                  else
                                  {}
                                      }//elementson.isNull

                                      nodeson=nodeson.nextSibling();
                                  }//while(!nodeson.isNull())

                              }
                              node2 = node2.nextSibling();//下一首曲子

                          }

                          //发送获取的信息到webtab,进行再处理
                          emit sendNetResult(namelist,
                                             lenthlist,
                                             artistlist,
                                             albumlist,
                                             songidlist);

                          //发送完毕后清空所有list
                          namelist = QStringList();
                          lenthlist = QStringList();
                          artistlist = QStringList();
                          albumlist = QStringList();
                          songidlist = QStringList();


                }
                node = node.nextSibling();
       }

}


/*
 * Function Name:getStrsongid
 * Description: songid的get函数
 * Created: 2015/9/5
 * Parameter: VOID
 * Return Code: QString
 * Author: 李雨峤
*/
QString Network::getStrsongid() const
{
    //songid的get函数
    //李雨峤 2015/9/5
    return strsongid;
}

void Network::setStrsongid(const QString &value)
{
    //songid的set函数
    //李雨峤 2015/9/5
    strsongid = value;
}

QString Network::getStrurl() const
{
    //url的get函数
    //李雨峤 2015/9/5
    return strurl;
}

void Network::setStrurl(const QString &value)
{
    //url的set函数
    //李雨峤 2015/9/5
    strurl = value;
}

QString Network::getStralbum() const
{
    //album的get函数
    //李雨峤 2015/9/5
    return stralbum;
}

void Network::setStralbum(const QString &value)
{
    //album的set函数
    //李雨峤 2015/9/5
    stralbum = value;
}

QString Network::getStrartist() const
{
    //artist的get函数
    //李雨峤 2015/9/5
    return strartist;
}

void Network::setStrartist(const QString &value)
{
    //artist的set函数
    //李雨峤 2015/9/5
    strartist = value;
}

QString Network::getStrlenth() const
{
    //lenth的get函数
    //李雨峤 2015/9/5
    return strlenth;
}

void Network::setStrlenth(const QString &value)
{
    //lenth的set函数
    //李雨峤 2015/9/5
    strlenth = value;
}

QString Network::getStrname() const
{
    //name的get函数
    //李雨峤 2015/9/5
    return strname;
}

void Network::setStrname(const QString &value)
{
    //name的set函数
    //李雨峤 2015/9/5
    strname = value;
}
