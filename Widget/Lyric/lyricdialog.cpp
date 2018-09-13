#include "lyricdialog.h"

#include <QDebug>
#include <QGridLayout>
#include <QFile>
#include <QMouseEvent>
#include <QMenu>
#include <QTimer>


LyricDialog::LyricDialog(QWidget *parent):QDialog(parent)
{
    setFixedSize(1400,150);
    move(462,850);

    //layout
    QGridLayout *layout = new QGridLayout (this);
    label1 = new LyricLabel (this);
    layout->addWidget(label1);
    label1->show();

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

}


/*
 * Function Name: getCurrentLine
 * Description: set label text for a time duration
 * Created: 18/09/09
 * Parameter: line QString
 *             time   qint64
 * Return Code: VOID
 * Author: Granx
*/
static QString lastLine = "";
void LyricDialog::getCurrentLine(QString line, qint64 time)
{

    // line isn't changed (maybe pause)
    if(lastLine == line)
    {
        return;
    }
    else
    {
        qDebug()<<line;
        label1->setText(line);
        label1->startLrcMask(time);

        //update lastLine
        lastLine = line;

    }
}

/*
 * Function Name: openLrc
 * Description: open, hide lrc
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void LyricDialog::openLrc(void)
{
    static int state = 0;
    if(state % 2 == 0)
    {
        hide();
    }
    else
    {
        show();
    }
    state++;
}


/*
 * Function Name: lockLrc
 * Description: lock, unlock lrc
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
static int stateLock = 1;
void LyricDialog::lockLrc()
{
    static int state = 1;
    if(state % 2 == 0)
    {
        stateLock = 1;
    }
    else
    {
        stateLock = 0;
    }
    state++;
}


/*
 * Function Name: mousePressEvent
 * Description: override mousePressEvent to achieve lock state, unlock state
 * Created: 18/09/09
 * Parameter: event QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void LyricDialog::mousePressEvent(QMouseEvent *event)
{
    if(stateLock == 0)
    {
        event->accept();
    }
    else if(event->button() == Qt::LeftButton)
    {
        offset = event->globalPos()-frameGeometry().topLeft();
    }
}

/*
 * Function Name: mouseMoveEvent
 * Description: override mouseMoveEvent to achieve lock state, unlock state
 * Created: 18/09/09
 * Parameter: event QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void LyricDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(stateLock == 0)
    {
        setCursor(Qt::ArrowCursor);
        event->accept();
    }
    else if(event->buttons()&Qt::LeftButton)
    {
        setCursor(Qt::PointingHandCursor);
        move(event->globalPos() - offset);
    }
}





