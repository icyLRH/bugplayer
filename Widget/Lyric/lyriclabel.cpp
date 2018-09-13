#include "lyriclabel.h"

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QFontMetrics>


#define  LENGTH      (fontM->boundingRect(text()).width() + 200)  //paint width + offset

#define  INTERVAL   5                                      //time interval between paintEvent
LyricLabel::LyricLabel(QWidget *parent) :QLabel(parent)
{
    //lyric
    linearGradient.setStart(0,10);
    linearGradient.setFinalStop(0,40);
    linearGradient.setColorAt(0.1,QColor(241,158,187));
    linearGradient.setColorAt(0.5,QColor(241,158,187));
    linearGradient.setColorAt(0.9,QColor(241,158,187));


    //mask
    maskLinearGradient.setStart(0,10);
    maskLinearGradient.setFinalStop(0,40);
    maskLinearGradient.setColorAt(0.1,QColor(55,175,255));
    maskLinearGradient.setColorAt(0.5,QColor(55,175,255));
    maskLinearGradient.setColorAt(0.9,QColor(55,175,255));

    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(40);

    fontM = new QFontMetrics (font);

    //timer initialize
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&LyricLabel::timeout);
    lrcMaskWidth = 0;
    lrcMaskWidthInterval = 0;

    //set default text
    setText("BugPlayer");
}

/*
 * Function Name: paintEvent
 * Description: override paintEvent to achieve mask
 * Created: 18/09/09
 * Parameter:  QPaintEvent *
 * Return Code: VOID
 * Author: Granx
*/
void LyricLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(font);

    //先绘制底层文字
    painter.setPen(QColor(255,255,255,255));
    painter.drawText(1,1,LENGTH,150,Qt::AlignLeft,text());

    //在上面绘制渐变文字
    painter.setPen(QPen(linearGradient,0));
    painter.drawText(0,0,LENGTH,150,Qt::AlignLeft,text());

    //设置歌词遮罩
    painter.setPen(QPen(maskLinearGradient,0));
    painter.drawText(0,0,lrcMaskWidth,150,Qt::AlignLeft,text());
}

void LyricLabel::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void LyricLabel::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}

/*
 * Function Name: startLrcMask
 * Description: if there is a new line, restart LrcMask
 * Created: 18/09/09
 * Parameter:  intervalTime qint64
 * Return Code: VOID
 * Author: Granx
*/
void LyricLabel::startLrcMask(qint64 intervalTime)
{
    qreal count = intervalTime / INTERVAL;

    //event INTERVAL mask widen
    lrcMaskWidthInterval = LENGTH/ count;

    //update last reset to 0
    lastLrcMaskTotalWidth = 0;
    start();

}

/*
 * Function Name: start
 * Description: read last width, update paintEvent, start
 * Created: 18/09/09
 * Parameter:  VOID
 * Return Code: VOID
 * Author: Granx
*/
void LyricLabel::start()
{
    //read last mask width
    //if a new line，last = 0
    //else paused，last != 0
    lrcMaskWidth = lastLrcMaskTotalWidth;
    timer->start(INTERVAL);
    update();
}

/*
 * Function Name: stop
 * Description: stop mask, save width
 * Created: 18/09/09
 * Parameter:  VOID
 * Return Code: VOID
 * Author: Granx
*/
void LyricLabel::stop()
{
    timer->stop();

    //save width
    lastLrcMaskTotalWidth = lrcMaskWidth;
    update();
}


/*
 * Function Name: timeout
 * Description: widen mask, update
 * Created: 18/09/09
 * Parameter:  VOID
 * Return Code: VOID
 * Author: Granx
*/
void LyricLabel::timeout()
{
    lrcMaskWidth += lrcMaskWidthInterval;
    update();
}
