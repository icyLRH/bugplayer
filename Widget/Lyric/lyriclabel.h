#ifndef LYRICLABEL_H
#define LYRICLABEL_H

#include <QWidget>
#include <QLabel>
class LyricLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LyricLabel(QWidget *parent = nullptr);
    void startLrcMask(qint64);
    void stop();
    void start();


signals:

public slots:
    void timeout();


protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    QLinearGradient linearGradient;
    QLinearGradient maskLinearGradient;
    QFont font;
    QFontMetrics *fontM;

    QTimer *timer;

    qreal lrcMaskWidth;             //width of dynamic mask

    qreal lrcMaskWidthInterval;     //every single width for mask to add

    qreal lastLrcMaskTotalWidth;    //last time mask total width

    QPoint offset;


};

#endif // LYRICLABEL_H
