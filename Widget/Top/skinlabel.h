#ifndef SKINLABEL_H
#define SKINLABEL_H

#include <QLabel>

class SkinLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SkinLabel(QWidget *parent = nullptr);

signals:
    void mouse_pressed(QPoint mouseLocalPos, QColor pointColor);//自定义信号

public slots:

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);
};

#endif // SKINLABEL_H
