#include "lyricdownload.h"

#include <QString>
#include <QByteArray>
#include <QEventLoop>
#include <QTimer>


QNetworkAccessManager *network_manager3 = new QNetworkAccessManager();
QNetworkRequest *network_request3 = new QNetworkRequest();
int i=0;
LyricDownload::LyricDownload(QWidget *parent) : QWidget(parent)
{

    //本类通过获取webtab传来的歌词链接，下载歌词文件到当前目录下的lyrics文件夹下
    //李雨峤 2015/9/7
    connect(this,&LyricDownload::setAlready,this,&LyricDownload::lyrDownload);
    connect(this,&LyricDownload::lastFinished,this,&LyricDownload::lyrDownload);
    connect(network_manager3, &QNetworkAccessManager::finished, this, &LyricDownload::lyrReplyFinished);


}

/*
 * Function Name: getLyric
 * Description: 获取名称和歌词链接
 * Created: 2015/9/7
 * Parameter: event QDragMoveEvent*
 * Return Code: VOID
 * Author: 李雨峤
*/
void LyricDownload::getLyric(QStringList lyrics, QStringList names)
{

    i = 0;
    namelist=names;
    lyriclist=lyrics;
    qDebug()<<namelist;
    qDebug()<<lyriclist;
    emit setAlready();
    qDebug()<<"setALready: ";
}

/*
 * Function Name: lyrDownload
 * Description: 发送与获得请求
 * Created: 2015/9/7
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void LyricDownload::lyrDownload()
{


    network_request3->setUrl(QUrl(lyriclist.at(i)));
    network_manager3->get(*network_request3);


}

/*
 * Function Name:lyrReplyFinished
 * Description: 获取响应的信息，状态码为200表示正常
 * Created: 2015/9/7
 * Parameter: QNetworkReply *reply
 * Return Code: VOID
 * Author: 李雨峤
*/
void LyricDownload::lyrReplyFinished(QNetworkReply *reply)
{


        QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug()<<status_code<<":3";

        //无错误返回
        if(reply->error() == QNetworkReply::NoError)
        {
            qDebug()<<i;

            //新建lyrics文件夹，如果存在则不创建
            QDir *temp = new QDir;
            bool exist = temp->exists("./lyrics");

            if(exist)
            qDebug()<<"文件夹已存在";
            else
            {
            bool ok = temp->mkdir("./lyrics");
            if( ok )
            qDebug()<<"创建成功";
            }

            //将歌词文件写入，命名为"name.lrc"
            QFile file(QString("./lyrics/%1.lrc").arg(namelist.at(i)));
            qDebug()<<namelist.at(i);


                //定义文件内容字符串
                QByteArray bytes= reply->readAll();
                QString content(bytes);

                    file.open(QIODevice::ReadWrite | QIODevice::Text);
                    //写入内容

                    QTextStream out(&file);
                    out<<content;
                    file.flush();

                //关闭文件
                file.close();


        }
        else
        {
            qDebug()<<"WRONG!(lyric)";

        }

        if(i<lyriclist.size()-1)
        {
             i++;
        emit lastFinished();//上一首已下载完毕，进入下一首

        }
        else
        {};


        reply->deleteLater();//删除reply
}


