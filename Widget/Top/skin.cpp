#include "skin.h"

#include <QApplication>
#include <QBoxLayout>
#include <QEvent>


Skin::Skin(QWidget *parent) : QDialog(parent),
    m_skinLabel(new SkinLabel (this))
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedSize(500,500);

    //layout
    QBoxLayout *layout = new QBoxLayout (QBoxLayout::LeftToRight,this);

    //addwidget
    layout->addWidget(skinLabel());
}

SkinLabel *Skin::skinLabel() const
{
    return m_skinLabel;
}

void Skin::setSkinLabel(SkinLabel *skinLabel)
{
    m_skinLabel = skinLabel;
}

/*
 * Function Name: resizeEvent
 * Description: auto hide
 * Created: 18/09/09
 * Parameter: event  QEvent *
 * Return Code: bool
 * Author: Granx
*/
bool Skin::event(QEvent *event)
{
    if(event->type() == QEvent::ActivationChange)
    {
        if(QApplication::activeWindow()!= this)
        {
            this->hide();
        }
    }
    return QDialog::event(event);
}
