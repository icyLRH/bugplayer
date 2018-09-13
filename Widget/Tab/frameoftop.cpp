#include "frameoftop.h"
#include "about.h"

#include <QFrame>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QSplitter>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>


FrameOfTop::FrameOfTop(QWidget *parent) : QWidget(parent),
    m_optionBtn(new QPushButton(this)),
    m_about(new About (this)),
    m_labelHorse(new QLabel (this)),
    m_searchEdit(new QLineEdit(this)),
    m_searchBtn(new QPushButton(this)),
    m_searchEdit2(new QLineEdit(this)),
    m_searchBtn2(new QPushButton(this)),
    m_skinBtn(new QPushButton(this)),
    m_userBtn(new QPushButton(this)),
    m_minimumBtn(new QPushButton(this)),
    m_exitBtn(new QPushButton(this)),
    m_selectBtn(new QPushButton (this)),
    m_scanBtn(new QPushButton (this))
{
    setAttribute(Qt::WA_TranslucentBackground);

    //edit place holder text
    searchEdit()->setPlaceholderText("Web:");
    searchEdit2()->setPlaceholderText("Local:");

    //max size
    optionBtn()->setMaximumSize(50,50);
    labelHorse()->setMaximumSize(270,30);
    searchEdit()->setMaximumSize(150,25);
    searchBtn()->setMaximumSize(20,20);
    searchEdit2()->setMaximumSize(150,25);
    searchBtn2()->setMaximumSize(20,20);
    skinBtn()->setMaximumSize(20,20);
    getUserBtn()->setMaximumSize(20,20);
    minimumBtn()->setMaximumSize(20,20);
    exitBtn()->setMaximumSize(20,20);
    getSelectBtn()->setMaximumSize(20,20);
    getScanBtn()->setMaximumSize(20,20);

    //min size
    optionBtn()->setMinimumSize(50,50);
    labelHorse()->setMinimumSize(150,30);
    searchEdit()->setMinimumSize(150,25);
    searchBtn()->setMinimumSize(20,20);
    searchEdit2()->setMinimumSize(150,25);
    searchBtn2()->setMinimumSize(20,20);
    skinBtn()->setMinimumSize(20,20);
    getUserBtn()->setMinimumSize(20,20);
    minimumBtn()->setMinimumSize(20,20);
    exitBtn()->setMinimumSize(20,20);
    getSelectBtn()->setMinimumSize(20,20);
    getScanBtn()->setMinimumSize(20,20);


    //layout
    QBoxLayout *boxLayoutOfFrame = new QBoxLayout(QBoxLayout::LeftToRight,this);

    //margins
    boxLayoutOfFrame->setContentsMargins(0,0,0,0);

    //space
    boxLayoutOfFrame->setSpacing(0);

    //spacer
    QSpacerItem *spacer1 = new QSpacerItem (100,10,QSizePolicy::MinimumExpanding,QSizePolicy::Fixed);
    QSpacerItem *spacer2 = new QSpacerItem (10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem *spacer3 = new QSpacerItem (15,15,QSizePolicy::Fixed,QSizePolicy::Fixed);
    QSpacerItem *spacer4 = new QSpacerItem (40,10,QSizePolicy::Fixed,QSizePolicy::Fixed);
    QSpacerItem *spacer5 = new QSpacerItem (15,15,QSizePolicy::Fixed,QSizePolicy::Fixed);
    QSpacerItem *spacer6 = new QSpacerItem (15,15,QSizePolicy::Fixed,QSizePolicy::Fixed);

    //addwidget
    boxLayoutOfFrame->addWidget(optionBtn());
    boxLayoutOfFrame->addSpacerItem(spacer1);
    boxLayoutOfFrame->addWidget(labelHorse());
    boxLayoutOfFrame->addSpacerItem(spacer2);
    boxLayoutOfFrame->addWidget(searchEdit2());
    boxLayoutOfFrame->addWidget(searchBtn2());
    boxLayoutOfFrame->addSpacerItem(spacer3);
    boxLayoutOfFrame->addWidget(searchEdit());
    boxLayoutOfFrame->addWidget(searchBtn());
    boxLayoutOfFrame->addSpacerItem(spacer4);   //alignTop
    boxLayoutOfFrame->addWidget(getScanBtn(),0,Qt::AlignTop);
    boxLayoutOfFrame->addWidget(getSelectBtn(),0,Qt::AlignTop);
    boxLayoutOfFrame->addWidget(skinBtn(),0,Qt::AlignTop);
    boxLayoutOfFrame->addSpacerItem(spacer5);
    boxLayoutOfFrame->addWidget(getUserBtn(),0,Qt::AlignTop);
    boxLayoutOfFrame->addSpacerItem(spacer6);
    boxLayoutOfFrame->addWidget(minimumBtn(),0,Qt::AlignTop);
    boxLayoutOfFrame->addWidget(exitBtn(),0,Qt::AlignTop);

    //connect user,min,exit,select,scan,skin
    connect(getUserBtn(),&QPushButton::clicked,this,&FrameOfTop::loging);
    connect(minimumBtn(),&QPushButton::clicked,this,&FrameOfTop::minimumBtnPressed);
    connect(exitBtn(),&QPushButton::clicked,this,&FrameOfTop::exitBtnPressed);
    connect(getSelectBtn(),&QPushButton::clicked,this,&FrameOfTop::selectBtnPressed);
    connect(getScanBtn(),&QPushButton::clicked,this,&FrameOfTop::scanBtnPressed);
    connect(skinBtn(),&QPushButton::clicked,this,&FrameOfTop::skinBtnPressed);

    //connect search
    connect(searchBtn(),&QPushButton::clicked,this,&FrameOfTop::searchBtnPressed);
    connect(searchEdit(),&QLineEdit::returnPressed,this,&FrameOfTop::searchBtnPressed);
    connect(searchBtn2(),&QPushButton::clicked,this,&FrameOfTop::searchBtn2Pressed);
    connect(searchEdit2(),&QLineEdit::returnPressed,this,&FrameOfTop::searchBtn2Pressed);
    connect(searchEdit2(),&QLineEdit::textChanged,this,&FrameOfTop::searchBtn2Pressed);

    //about page
    connect(optionBtn(),&QPushButton::clicked,about(),&About::show);

    //horse label
    m_timer = new QTimer (this);
    connect(m_timer,&QTimer::timeout,this,&FrameOfTop::horseLabelGo);
    m_timer->start(1000);
    nPos = 0;

    //set styles sheet
    customStylesSheet();
}

/*
 * Function Name: customStyleSheet
 * Description: set styles sheet
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::customStylesSheet()
{
    optionBtn()->setStyleSheet("QPushButton{border-image:url(:/Icon/src/Icon/BugPlayer4.png);}");

    labelHorse()->setStyleSheet("QLabel{color:rgba(0,0,0,180); font-weight: bold; font-size: 18px; font-family: 等线}");


    getUserBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/middlewidget/btn_cloud (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/src/middlewidget/btn_cloud (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/src/middlewidget/btn_cloud (3).png);}");

    m_minimumBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_mini (1).png);}"
                                "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_mini (2).png);}"
                                "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_mini (3).png);}");


    searchBtn()->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_search (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_search (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_search (3).png);}");

    searchBtn2()->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_search (1).png);}"
                                "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_search (2).png);}"
                                "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_search (3).png);}");


    m_exitBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_close (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_close (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_close (3).png);}");


    m_searchEdit->setStyleSheet("QLineEdit{border-radius:9px;background:rgb(255,255,255,180);}");

    m_searchEdit2->setStyleSheet("QLineEdit{border-radius:9px;background:rgb(255,255,255,180);}");

    m_selectBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_tool (1).png);}"
                               "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_tool (2).png);}"
                               "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_tool (3).png);}");

    m_scanBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_refresh(1).png);}"
                             "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_refresh(2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_refresh(3).png);}");

    m_skinBtn->setStyleSheet("QPushButton{border-image:url(:/image/src/topwidget/btn_skin (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/src/topwidget/btn_skin (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/src/topwidget/btn_skin (3).png);}");

}

/*
 * Function Name: setLabelHorseString
 * Description: set horse label content labelHorseString
 * Created: 18/09/09
 * Parameter: labelHorseString  const QString &
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::setLabelHorseString(const QString &labelHorseString)
{
    m_labelHorseString = "当前播放：" + labelHorseString;
}

/*
 * Function Name: getNameAndArtist
 * Description: get name, artist for horse label, reset horse label show pos, timer.
 * Created: 18/09/09
 * Parameter: name  QString
 *           artist QString
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::getNameAndArtist(const QString name, const QString artist)
{
    m_timer->stop();

    setLabelHorseString(name + "-" + artist);
    setLastLabelHorseString("");

    //reset pos
    nPos = 0;

    //restart timer
    m_timer->start(1000);
}

void FrameOfTop::selectBtnPressed()
{
    emit selected();
}

void FrameOfTop::scanBtnPressed()
{
    emit scaned();
}

/*
 * Function Name: horseLabelGo
 * Description: achieve scroll
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::horseLabelGo()
{

    if (nPos > labelHorseString().length())
    {
        m_labelHorseString = lastLabelHorseString();
        nPos = 1;
    }

    //get remaining string
    QString temp1 = labelHorseString().mid(nPos);
    //get string cut off
    QString temp2 = labelHorseString().replace(temp1,"");

    setLastLabelHorseString(temp1 + "          " + temp2);
    labelHorse()->setText(lastLabelHorseString());

    nPos++;
}


QPushButton *FrameOfTop::optionBtn() const
{
    return m_optionBtn;
}

void FrameOfTop::setOptionBtn(QPushButton *optionBtn)
{
    m_optionBtn = optionBtn;
}

QLineEdit *FrameOfTop::searchEdit() const
{
    return m_searchEdit;
}

void FrameOfTop::setSearchEdit(QLineEdit *searchEdit)
{
    m_searchEdit = searchEdit;
}

QPushButton *FrameOfTop::skinBtn() const
{
    return m_skinBtn;
}

void FrameOfTop::setSkinBtn(QPushButton *skinBtn)
{
    m_skinBtn = skinBtn;
}


QPushButton *FrameOfTop::minimumBtn() const
{
    return m_minimumBtn;
}

void FrameOfTop::setMinimumBtn(QPushButton *minimumBtn)
{
    m_minimumBtn = minimumBtn;
}

QPushButton *FrameOfTop::exitBtn() const
{
    return m_exitBtn;
}

void FrameOfTop::setExitBtn(QPushButton *exitBtn)
{
    m_exitBtn = exitBtn;
}

void FrameOfTop::exitBtnPressed()
{
    parentWidget()->close();
}

/*
 * Function Name: minimumBtnPressed
 * Description: hide player
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::minimumBtnPressed()
{
    parentWidget()->hide();
}


/*
 * Function Name: searchBtnPressed
 * Description: emit search content
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::searchBtnPressed()
{
    emit sendText(QString(searchEdit()->text()));
}

/*
 * Function Name: searchBtn2Pressed
 * Description: emit search content
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::searchBtn2Pressed()
{
    emit sendText2(QString(searchEdit2()->text()));
}

/*
 * Function Name: mousePressEvent
 * Description: achieve window move
 * Created: 18/09/09
 * Parameter: event QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        offset = event->globalPos()-parentWidget()->frameGeometry().topLeft();
    }
}

/*
 * Function Name: mouseMoveEvent
 * Description: achieve window move
 * Created: 18/09/09
 * Parameter: event QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::mouseMoveEvent(QMouseEvent *event)
{
    //if max already
    // reset size
    if(parentWidget()->windowState()==Qt::WindowMaximized)
    {
        double relative = double(event->pos().x()) / parentWidget()->width();
        double relative1 = relative * (parentWidget()->normalGeometry().width());
        parentWidget()->setWindowState(Qt::WindowNoState);
        parentWidget()->move(event->globalPos().x() - relative1, 0);
        offset = event->globalPos()-parentWidget()->frameGeometry().topLeft();

    }

    if(event->buttons()&Qt::LeftButton)
    {
        parentWidget()->move(event->globalPos() - offset);
    }

}

void FrameOfTop::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

/*
 * Function Name: mouseDoubleClickEvent
 * Description: achieve window max, min
 * Created: 18/09/09
 * Parameter: event QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void FrameOfTop::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(parentWidget()->windowState()==Qt::WindowNoState)
    {
        parentWidget()->setWindowState(Qt::WindowMaximized);
    }
    else if(parentWidget()->windowState()==Qt::WindowMaximized)
    {
        parentWidget()->setWindowState(Qt::WindowNoState);
    }
    event->accept();
}

QPushButton *FrameOfTop::getUserBtn() const
{
    return m_userBtn;
}

void FrameOfTop::setUserBtn(QPushButton *userBtn)
{
    m_userBtn = userBtn;
}

void FrameOfTop::skinBtnPressed()
{
    emit skined();
}

QPushButton *FrameOfTop::getScanBtn() const
{
    return m_scanBtn;
}

void FrameOfTop::setScanBtn(QPushButton *scanBtn)
{
    m_scanBtn = scanBtn;
}

QPushButton *FrameOfTop::getSelectBtn() const
{
    return m_selectBtn;
}

void FrameOfTop::setSelectBtn(QPushButton *selectBtn)
{
    m_selectBtn = selectBtn;
}

QTimer *FrameOfTop::getTimer() const
{
    return m_timer;
}

void FrameOfTop::setTimer(QTimer *timer)
{
    m_timer = timer;
}

QString FrameOfTop::lastLabelHorseString() const
{
    return m_lastLabelHorseString;
}

void FrameOfTop::setLastLabelHorseString(const QString &lastLabelHorseString)
{
    m_lastLabelHorseString = lastLabelHorseString;
}

QString FrameOfTop::labelHorseString() const
{
    return m_labelHorseString;
}


QLabel *FrameOfTop::labelHorse() const
{
    return m_labelHorse;
}

void FrameOfTop::setLabelHorse(QLabel *labelHorse)
{
    m_labelHorse = labelHorse;
}

About *FrameOfTop::about() const
{
    return m_about;
}

void FrameOfTop::setAbout(About *about)
{
    m_about = about;
}

QPushButton *FrameOfTop::searchBtn2() const
{
    return m_searchBtn2;
}

void FrameOfTop::setSearchBtn2(QPushButton *searchBtn2)
{
    m_searchBtn2 = searchBtn2;
}

void FrameOfTop::userBtnPressed()
{
    emit loging();
}

QLineEdit *FrameOfTop::searchEdit2() const
{
    return m_searchEdit2;
}

void FrameOfTop::setSearchEdit2(QLineEdit *searchEdit2)
{
    m_searchEdit2 = searchEdit2;
}

QPushButton *FrameOfTop::searchBtn() const
{
    return m_searchBtn;
}

void FrameOfTop::setSearchBtn(QPushButton *searchBtn)
{
    m_searchBtn = searchBtn;
}


