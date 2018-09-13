#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QPixmap>
#include <QLabel>


class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void focusOutEvent(QFocusEvent* event);
    void focusInEvent(QFocusEvent *event);
};

#endif // ABOUT_H
