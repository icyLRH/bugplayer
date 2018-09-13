#include "newplayer.h"

#include<QDebug>
#include<QMediaPlaylist>

//全局变量 进度条值和默认音量值
const int maxValue = 1000;
const int defaultVolume = 33;

NewPlayer::NewPlayer(QWidget *parent) :
    Player(parent)
{
    m_mediaPlayer = new QMediaPlayer(this);//初始化播放器
    m_songlist = new QMediaPlaylist(this);//初始化播放列表

    //计时器启动
    timer =new QTimer(this);//计时器
    timer2 = new QTimer(this);//lyq
    timer->setInterval(1000);
    timer2->setInterval(1);//lyq
    timer2->start();//lyq
    time1.setHMS(0,0,0);//初始化time1对象,时分秒

    //暂停按键
    connect(tray()->trayMenu(),
            &TrayMenu::playAction,
            this,
            &NewPlayer::PlbtClicked);
    connect(frameOfBottom()->playBtn(),
            &QPushButton::clicked,
            this,
            &NewPlayer::PlbtClicked);

    //上一首、下一首按键
    connect(frameOfBottom()->nextTrackBtn(),
            &QPushButton::clicked,
            this,
            &NewPlayer::nextBtnClicked);
    connect(frameOfBottom()->previousTrackBtn(),
            &QPushButton::clicked,
            this,
            &NewPlayer::preBtnClicked);
    connect(tray()->trayMenu(),
            &TrayMenu::nextAction,
            this,
            &NewPlayer::nextBtnClicked);
    connect(tray()->trayMenu(),
            &TrayMenu::PreAction,
            this,
            &NewPlayer::preBtnClicked);

    //播放模式按键
    connect(frameOfBottom()->modeBtn(),
            &QPushButton::clicked,
            this,
            &NewPlayer::modeBtnClicked);

    //音量条
    frameOfBottom()->volumnSlider()->setRange(0,100);
    frameOfBottom()->volumnSlider()->setValue(defaultVolume);
    connect(frameOfBottom()->volumnSlider(),
            &CustomSlider::valueChanged,
            this,
            &NewPlayer::VosValueChanged);

    //进度条设置

    frameOfBottom()->timeBarSlider()->setRange(0,maxValue);
    frameOfBottom()->timeBarSlider()->setEnabled(false);
    connect(timer,
            &QTimer::timeout,
            this,
            &NewPlayer::onTimerOut);
    connect(timer,
            &QTimer::timeout,
            this,
            &NewPlayer::updateTime);

    connect(timer2,
            &QTimer::timeout,
            this,
            &NewPlayer::onTimer2Out);//lyq 10ms发射一次

    connect(frameOfBottom()->timeBarSlider(),
            &CustomSlider::costomSliderClicked,
            this,
            &NewPlayer::timSldClicked);
    connect(frameOfBottom()->timeBarSlider(),
            &CustomSlider::sliderMoved,
            this,
            &NewPlayer::timSldMoved);
    connect(frameOfBottom()->timeBarSlider(),
            &CustomSlider::sliderReleased,
            this,
            &NewPlayer::timSldReleased);

    //创建播放器
    //（默认歌曲，检测用）m_mediaPlayer->setMedia(QUrl::fromLocalFile("http://zhangmenshiting.qianqian.com/data2/music/98373354e92080f08c9b401e421aff72/596586949/596586949.mp3?xcode=30dea427a411a2e8a0cc505dc0621a48"));
    connect(playTab()->defaultTab(),
            &DefaultTab::sendUrl,
            this,
            &NewPlayer::getUrl);


    connect(playTab(),
            &PlayTab::freshOver,
            this,
            &NewPlayer::addConnect);//zh
    connect(this,
            &NewPlayer::sendCurrentms,
            lyric(),
            &Lyric::getCurrentms);//zh
    connect(playTab()->webTab(),
            &WebTab::sendUrl,
            this,
            &NewPlayer::getUrl);
    connect(playTab()->listTab(),
            &ListTab::sendUrl,
            this,
            &NewPlayer::getUrl);//zh

    //listtab flash刷新后自动播放
    connect(playTab()->listTab(),
            &ListTab::flashOver,
            this,
            &NewPlayer::PlbtClicked);


    //加入播放列表
    playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::Loop);//默认模式为列表循环
    m_mediaPlayer->setPlaylist(playTab()->listTab()->Playlist());//将播放列表加载到播放器中
//    m_mediaPlayer->play();


    //获取媒体总时长
    connect(m_mediaPlayer,
            &QMediaPlayer::durationChanged,
            this,
            &NewPlayer::setMediaDuration);

    connect(this,
            &NewPlayer::durationOk,
            this,
            &NewPlayer::durationReady);

}//构造函数结束

/*
 * Function Name:getMediaDuration
 * Description: 获取媒体总时长
 * Created: 2015/8/23
 * Parameter: VOID
 * Return Code: qint64
 * Author: 李雨峤
*/
qint64 NewPlayer::getMediaDuration()
{

    //    qDebug()<<m_totalTime;
    return m_totalTime;

}

qint64 current_position,old_position;//当前与上一次的播放位置

/*
 * Function Name:setMediaDuration
 * Description: 用于间接获取媒体的duration,并打印在time标签上（只在信号槽中有用，否则为零）
 * Created: 2015/8/23
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::setMediaDuration()
{


   qint64 tottime =( m_mediaPlayer->duration())/1000;

   //转化为时间格式
   time1.setHMS(0,
                tottime/60,
                tottime%60,0);
    frameOfBottom()->time2Label()->setText(time1.toString("mm:ss"));

    m_totalTime = m_mediaPlayer->duration();
    emit durationOk();//时长获取完毕
}

/*
 * Function Name:updateTime
 * Description: 本函数与定时器相连,每一秒钟进入一次
 * Created: 2015/8/24
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::updateTime()
{


    time2.setHMS(0,
                 m_mediaPlayer->position()/1000/60,
                 m_mediaPlayer->position()/1000%60,
                 0);
    frameOfBottom()->time1Label()->setText(time2.toString("mm:ss"));//获取time时间值,转化成string,"mm:ss"表示这里我们只要分和秒就够了

}

/*
 * Function Name:onTimerOut
 * Description: 与计时器相连，设置进度条位置
 * Created: 2015/8/25
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::onTimerOut()
{

    if(getMediaDuration()==0)
    {
        //防止除零错误
        return;
    }
    else
    {
    frameOfBottom()->timeBarSlider()->
            setSliderPosition(m_mediaPlayer->
                              position()*maxValue/m_totalTime);
    }

}

/*
 * Function Name:onTimer2Out
 * Description: 发送当前播放时间，用于歌词设置
 * Created:  2015/9/6
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::onTimer2Out()
{

    qint64 curr = m_mediaPlayer->position();
    emit sendCurrentms(curr);
}

/*
 * Function Name:timSldClicked
 * Description: 进度条点击事件
 * Created:  2015/8/28
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::timSldClicked()
{

     m_mediaPlayer->setPosition(frameOfBottom()->
                                timeBarSlider()->
                                value()*getMediaDuration()/maxValue);

}

/*
 * Function Name:timSldMoved
 * Description: 进度条移动事件
 * Created:  2015/8/28
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::timSldMoved()
{

    timer->stop();
    m_mediaPlayer->pause();
}


/*
 * Function Name:timSldReleased
 * Description: 进度条释放事件
 * Created:  2015/8/28
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::timSldReleased()
{

    m_mediaPlayer->setPosition(frameOfBottom()->
                               timeBarSlider()->
                               value()*getMediaDuration()/maxValue);
    m_mediaPlayer->play();
    timer->start();
}

/*
 * Function Name:startLrc
 * Description: 给playlist 自动切换用的歌词启动器
 * Created:  2015/9/2
 * Parameter: const QMediaContent &mediaContent
 * Return Code: VOID
 * Author: 钟昊
*/
void NewPlayer::startLrc(const QMediaContent &mediaContent)
{

    lyric()->url = mediaContent.canonicalUrl().toString();
    lyric()->startLyric(getMediaDuration());//歌词部署开始 zh
}

void NewPlayer::single()
{
    playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    frameOfBottom()->modeBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listscircle_single (1).png);}"
                                              "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listscircle_single (2).png);}");
}

void NewPlayer::random()
{
    playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::Random);
    frameOfBottom()->modeBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listrandom (1).png);}"
                                              "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listrandom (2).png);}");
}

void NewPlayer::loop()
{
    playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::Loop);
    frameOfBottom()->modeBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listcircle (1).png);}"
                                              "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listcircle (2).png);}");
}

/*
 * Function Name:getUrl
 * Description: 获取到当前歌曲条目的url,对其进行播放等操作
 * Created:  2015/9/2
 * Parameter: QString url
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::getUrl(QString url)
{

    timer->stop();  //lyq
    m_mediaPlayer->stop();      //lyq

    m_mediaPlayer->setVolume(frameOfBottom()->volumnSlider()->value());//设置音量

    qDebug()<<"添加成功";
    //zh
    lyric()->url = url;
    lyric()->startLyric(getMediaDuration());//歌词部署开始 zh

    frameOfBottom()->timeBarSlider()->setEnabled(true);//进度条解禁

    m_mediaPlayer->play();//媒体播放

    emit sendDuration();
    //样式加入
    frameOfBottom()->playBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_pause (1).png);}"
                                               "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_pause (2).png);}"
                                               "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_pause (3).png);}");

}

//zh
void NewPlayer::addConnect()
{
    connect(playTab()->table(),
            &DefaultTable::sendUrl,
            this,
            &NewPlayer::getUrl);
}

/*
 * Function Name:nextBtnClicked
 * Description: 下一首按键功能
 * Created:  2015/9/3
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::nextBtnClicked()
{

    frameOfBottom()->timeBarSlider()->setEnabled(true);
    qDebug()<<"clicked!";

    playTab()->listTab()->Playlist()->next();

    lyric()->url = playTab()->listTab()->Playlist()->currentMedia().canonicalUrl().toString();
    lyric()->startLyric(getMediaDuration());//歌词部署开始 zh

    m_mediaPlayer->play();
    emit sendDuration();
}

/*
 * Function Name:preBtnClicked
 * Description: 上一首按键功能
 * Created:  2015/9/3
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::preBtnClicked()
{

    frameOfBottom()->timeBarSlider()->setEnabled(true);
    qDebug()<<"clicked!";

    playTab()->listTab()->Playlist()->previous();

    lyric()->url = playTab()->listTab()->Playlist()->currentMedia().canonicalUrl().toString();
    lyric()->startLyric(getMediaDuration());//歌词部署开始 zh

    m_mediaPlayer->play();
    emit sendDuration();
}

/*
 * Function Name:modeBtnClicked
 * Description: 播放模式按键
 * Created:  2015/9/4
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::modeBtnClicked()
{

    QMediaPlaylist::PlaybackMode mode = playTab()->listTab()->Playlist()->playbackMode();

    //每进入一次，判断当前播放模式并修改
    //顺序为 列表循环->随机播放->单曲循环->列表循环
    if(mode == QMediaPlaylist::CurrentItemInLoop)
    {
        playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::Loop);
        qDebug()<<"列表循环";

        frameOfBottom()->modeBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listcircle (1).png);}"
                                                  "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listcircle (2).png);}");
    }
    else if(mode == QMediaPlaylist::Loop)
    {
        playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::Random);
        qDebug()<<"随机播放";

        frameOfBottom()->modeBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listrandom (1).png);}"
                                                  "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listrandom (2).png);}");
    }
    else if(mode == QMediaPlaylist::Random)
    {
        playTab()->listTab()->Playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        qDebug()<<"单曲循环";

        frameOfBottom()->modeBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listscircle_single (1).png);}"
                                                  "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listscircle_single (2).png);}");
    }
    else
    {
        qDebug()<<"???mode";
    }
}

/*
 * Function Name:PlbtClicked
 * Description: 播放/暂停按键
 * Created:  2015/8/20
 * Parameter: VOID
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::PlbtClicked()
{


        if (m_mediaPlayer->state() == QMediaPlayer::PlayingState)
           {//如果当前处于播放状态
            m_mediaPlayer->pause();
            timer->stop();

            frameOfBottom()->playBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_play (1).png);}"
                                                       "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_play (2).png);}"
                                                       "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_play (3).png);}");


            lyric()->lyricDialog->label1->stop();

            }
        else
            {
            //如果当前无媒体可播放
            if(m_mediaPlayer->playlist()->isEmpty())
            {
                qDebug()<<"当前无媒体！";
            }

            else
            {
            m_mediaPlayer->play();
           timer->start();

           frameOfBottom()->playBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_pause (1).png);}"
                                                      "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_pause (2).png);}"
                                                      "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_pause (3).png);}");

            lyric()->lyricDialog->label1->start();
            frameOfBottom()->timeBarSlider()->setEnabled(true);//进度条解禁
            }
            }


}

/*
 * Function Name:VosValueChanged
 * Description:音量调整
 * Created:  2015/8/21
 * Parameter: int value
 * Return Code: VOID
 * Author: 李雨峤
*/
void NewPlayer::VosValueChanged(int value)
{

    m_mediaPlayer->setVolume(value);
}


QMediaPlayer *NewPlayer::getMediaPlayer() const
{
    return m_mediaPlayer;
}

void NewPlayer::setMediaPlayer(QMediaPlayer *mediaPlayer)
{
    m_mediaPlayer = mediaPlayer;
}

void NewPlayer::durationReady()
{
    timer->start();
}



QMediaPlaylist *NewPlayer::getSonglist() const
{
    return m_songlist;
}

void NewPlayer::setSonglist(QMediaPlaylist *songlist)
{
    m_songlist = songlist;
}



