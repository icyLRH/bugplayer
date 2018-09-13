#include "customslider.h"


/*
 * Function Name: mousePressEvent
 * Description: 重写鼠标单击事件
 * Created: 2015/9/7
 * Parameter: event QDragMoveEvent*
 * Return Code: VOID
 * Author: 李雨峤
*/
void CustomSlider::mousePressEvent(QMouseEvent *event)
{


    //注意应先调用父类的鼠标点击处理事件，这样可以不影响拖动的情况
    QSlider::mousePressEvent(event);

    //获取鼠标的位置，这里并不能直接从ev中取值（因为如果是拖动的话，鼠标开始点击的位置没有意义了）
    double pos = event->pos().x() / (double)width();
    setValue(pos * (maximum() - minimum()) + minimum());

    //发送自定义的鼠标单击信号
    emit costomSliderClicked();
}
