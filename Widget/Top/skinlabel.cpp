#include "skinlabel.h"

#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>


SkinLabel::SkinLabel(QWidget *parent) : QLabel(parent)
{

}


/*
 * Function Name: mousePressEvent
 * Description: grab 1 rgb, emit
 * Created: 18/09/09
 * Parameter: e  QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void SkinLabel::mousePressEvent(QMouseEvent *e)
{
    QPoint mouse_local_pos = e->pos();
    QPixmap pixmap = this->grab(QRect(mouse_local_pos, QSize(1,1)));
    QRgb rgb = pixmap.toImage().pixel(0,0);
    qDebug()<<mouse_local_pos;
    emit mouse_pressed(mouse_local_pos, QColor(rgb));
}

/*
 * Function Name: mouseMoveEvent
 * Description: grab 1 rgb, emit
 * Created: 18/09/09
 * Parameter: e  QMouseEvent *
 * Return Code: VOID
 * Author: Granx
*/
void SkinLabel::mouseMoveEvent(QMouseEvent *e)
{
    QPoint mouse_local_pos = e->pos();
    QPixmap pixmap = this->grab(QRect(mouse_local_pos, QSize(1,1)));
    QRgb rgb = pixmap.toImage().pixel(0,0);

    //(243,231)is the point of center of circle, 164 is radius.
    if((mouse_local_pos.x() - 243) * (mouse_local_pos.x() - 243) +(mouse_local_pos .y() - 231) * (mouse_local_pos .y() - 231) > 164 * 164)
    {
        emit mouse_pressed(mouse_local_pos, QColor());
    }
    else
    {
        emit mouse_pressed(mouse_local_pos, QColor(rgb));
    }

}

/*
 * Function Name: resizeEvent
 * Description: achieve pixmap scaled
 * Created: 18/09/09
 * Parameter: e  QResizeEvent *
 * Return Code: VOID
 * Author: Granx
*/
void SkinLabel::resizeEvent(QResizeEvent *e)
{
    QPixmap pix(":/image/src/skin/skin.png");
    pix = pix.scaled(size(),Qt::KeepAspectRatio);
    setPixmap(pix);
}
