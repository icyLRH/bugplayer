#include "frameofbottom.h"

#include <QFrame>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QBoxLayout>
#include <QSpacerItem>


FrameOfBottom::FrameOfBottom(QWidget *parent) : QWidget(parent),
    //initialize
    m_previousTrackBtn(new QPushButton (this)),
    m_nextTrackBtn (new QPushButton (this)),
    m_playBtn(new QPushButton (this)),
    m_time1Label(new QLabel ("00:00",this)),
    m_time2Label(new QLabel ("00:00",this)),
    m_timeBarSlider(new CustomSlider (Qt::Horizontal,this)),
    m_volumnSlider(new QSlider (Qt::Horizontal,this)),
    m_lrcOpenBtn(new QPushButton (this)),
    m_modeBtn(new QPushButton (this))
{

    setAttribute(Qt::WA_TranslucentBackground);

    //maxmumsize
    previousTrackBtn()->setMaximumSize(50,50);
    playBtn()->setMaximumSize(50,50);
    nextTrackBtn()->setMaximumSize(50,50);
    time1Label()->setMaximumSize(40,40);
    time2Label()->setMaximumSize(40,40);
    volumnSlider()->setMaximumSize(100,15);
    modeBtn()->setMaximumSize(20,20);
    lrcOpenBtn()->setMaximumSize(20,20);

    //minimumsize
    previousTrackBtn()->setMinimumSize(50,50);
    playBtn()->setMinimumSize(50,50);
    nextTrackBtn()->setMinimumSize(50,50);
    time1Label()->setMinimumSize(40,40);
    time2Label()->setMaximumSize(40,40);
    volumnSlider()->setMinimumSize(100,15);
    modeBtn()->setMinimumSize(20,20);
    lrcOpenBtn()->setMinimumSize(20,20);

    //layout
    QBoxLayout *boxLayoutOfFrame = new QBoxLayout(QBoxLayout::LeftToRight, this);

    //addwidget
    boxLayoutOfFrame->addWidget(previousTrackBtn());
    boxLayoutOfFrame->addWidget(playBtn());
    boxLayoutOfFrame->addWidget(nextTrackBtn());
    boxLayoutOfFrame->addWidget(time1Label());

    boxLayoutOfFrame->addWidget(timeBarSlider());

    boxLayoutOfFrame->addWidget(time2Label());
    boxLayoutOfFrame->addWidget(volumnSlider());
    boxLayoutOfFrame->addWidget(modeBtn());
    boxLayoutOfFrame->addWidget(lrcOpenBtn());

    //set styles sheet
    customStyleSheet();
}

QPushButton *FrameOfBottom::previousTrackBtn() const
{
    return m_previousTrackBtn;
}

void FrameOfBottom::setPreviousTrackBtn(QPushButton *previousTrackBtn)
{
    m_previousTrackBtn = previousTrackBtn;
}

QPushButton *FrameOfBottom::nextTrackBtn() const
{
    return m_nextTrackBtn;
}

void FrameOfBottom::setNextTrackBtn(QPushButton *nextTrackBtn)
{
    m_nextTrackBtn = nextTrackBtn;
}

QPushButton *FrameOfBottom::playBtn() const
{
    return m_playBtn;
}

void FrameOfBottom::setPlayBtn(QPushButton *playBtn)
{
    m_playBtn = playBtn;
}

QLabel *FrameOfBottom::time1Label() const
{
    return m_time1Label;
}

void FrameOfBottom::setTime1Label(QLabel *time1Label)
{
    m_time1Label = time1Label;
}

QLabel *FrameOfBottom::time2Label() const
{
    return m_time2Label;
}

void FrameOfBottom::setTime2Label(QLabel *time2Label)
{
    m_time2Label = time2Label;
}

CustomSlider *FrameOfBottom::timeBarSlider() const
{
    return m_timeBarSlider;
}

void FrameOfBottom::setTimeBarSlider(CustomSlider *timeBarSlider)
{
    m_timeBarSlider = timeBarSlider;
}

QSlider *FrameOfBottom::volumnSlider() const
{
    return m_volumnSlider;
}

void FrameOfBottom::setVolumnSlider(QSlider *volumnSlider)
{
    m_volumnSlider = volumnSlider;
}

QPushButton *FrameOfBottom::lrcOpenBtn() const
{
    return m_lrcOpenBtn;
}

void FrameOfBottom::setLrcOpenBtn(QPushButton *lrcOpenBtn)
{
    m_lrcOpenBtn = lrcOpenBtn;
}

QPushButton *FrameOfBottom::modeBtn() const
{
    return m_modeBtn;
}

void FrameOfBottom::setModeBtn(QPushButton *modeBtn)
{
    m_modeBtn = modeBtn;
}

/*
 * Function Name: customStyleSheet
 * Description: set styles sheet
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfBottom::customStyleSheet()
{
    m_nextTrackBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_next (1).png);}"
                                  "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_next (2).png);}"
                                  "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_next (3).png);}");


    m_previousTrackBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_previous (1).png);}"
                                      "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_previous (2).png);}"
                                      "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_previous (3).png);}");


    m_playBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_play (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_play (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_play (3).png);}");


    m_timeBarSlider->setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:3px;}"
                                   "QSlider::sub-page:horizontal{background:rgb(255, 255, 160);}"
                                   "QSlider::add-page:horizontal{background:rgb(200,200,209);}"
                                   "QSlider::handle:horizontal{background:rgb(255, 255, 160);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");


    m_lrcOpenBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_lrc (1).png);}"
                                "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_lrc (2).png);}"
                                "QPushButton::pressed{border-image:url(:/image/src/bottomwidget/btn_lrc (3).png);}");


    m_volumnSlider->setStyleSheet("QSlider::groove:horizontal{border-radius:2px;height:2px;}"
                                  "QSlider::sub-page:horizontal{background:rgb(104,104,104);}"
                                  "QSlider::add-page:horizontal{background:rgb(209,209,209);}"
                                  "QSlider::handle:horizontal{background:rgb(104,104,104);width:8px;border-radius:4px;margin:-3px 0px -3px 0px;}");


    m_volumnSlider->setCursor(Qt::PointingHandCursor);


    m_modeBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/bottomwidget/btn_listcircle (1).png);}"
                                              "QPushButton::hover{border-image:url(:/image/src/bottomwidget/btn_listcircle (2).png);}");


    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(12);
    font.setBold(false);
    m_time1Label->setFont(font);
    m_time2Label->setFont(font);

}

