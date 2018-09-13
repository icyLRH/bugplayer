#include "about.h"

#include <QBoxLayout>
#include <QPropertyAnimation>


About::About(QWidget *parent) : QDialog(parent)
{
    //background translucent
    setAttribute(Qt::WA_TranslucentBackground);

    //window opacity
    setWindowOpacity(0);

    //indicates it's a window and framelessWindowHint
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //pixmap
    QPixmap pixmap (":/Icon/src/Icon/BugPlayer3.png");
    QLabel * label1 = new QLabel (this);
    label1->setPixmap(pixmap);
    label1->resize(pixmap.size());

    //label
    QFont font;
    font.setFamily("华文行楷");
    font.setPixelSize(25);
    QLabel * label2 = new QLabel (this);
    label2->setFont(font);
    label2->setText("开发人员：李若涵，李雨峤，钟昊。");

    //layout
    QBoxLayout * layout = new QBoxLayout (QBoxLayout::BottomToTop,this);
    layout->addWidget(label2);
    layout->addWidget(label1);

    //focus ready
    setFocus();
}

/*
 * Function Name: focusOutEvent.
 * Description: override the function focusOutEvent, when it loses focus, after a short animation, hide.
 * Created: 18/09/09
 * Parameter: event QFocusEvent *
 * Return Code: VOID
 * Author: Granx
*/
void About::focusOutEvent(QFocusEvent *event)
{
    //creat QPropertyAnimation object
    QPropertyAnimation * animation = new QPropertyAnimation(this, "windowOpacity");

    //duration
    animation->setDuration(600);

    //startValue
    animation->setStartValue(1);

    //endValue
    animation->setEndValue(0);

    //connect, finished then hide
    connect(animation,&QPropertyAnimation::finished,this,hide);

    //animation start
    animation->start();
}

/*
 * Function Name: focusInEvent.
 * Description: override the function focusInEvent, when it get focus, after a short animation, show.
 * Created: 18/09/09
 * Parameter: event QFocusEvent *
 * Return Code: VOID
 * Author: Granx
*/
void About::focusInEvent(QFocusEvent *event)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(600);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    connect(animation,&QPropertyAnimation::finished,this,show);
}
