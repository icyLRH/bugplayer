#ifndef LYRICDIALOG_H
#define LYRICDIALOG_H

#include <QDialog>
#include <QLabel>
#include "lyriclabel.h"

class LyricDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LyricDialog(QWidget *parent = nullptr);

    LyricLabel *label1;

signals:

public slots:
    void getCurrentLine(QString line, qint64 time);
    void openLrc(void);
    void lockLrc(void);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint offset;
};



#endif // LYRICDIALOG_H
