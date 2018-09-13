#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QApplication>


class CustomSlider : public QSlider
{
    Q_OBJECT
public:

    CustomSlider(Qt::Orientation orientation, QWidget *parent):QSlider(orientation,parent)
    {

    }

protected:
    void mousePressEvent(QMouseEvent *event);   //重写QSlider的mousePressEvent事件
signals:
    void costomSliderClicked();     //自定义的鼠标单击信号，用于捕获并处理

public slots:
};



#endif // CUSTOMSLIDER_H
