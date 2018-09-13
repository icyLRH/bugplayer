#ifndef TRAY_H
#define TRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <traymenu.h>
class Tray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit Tray(QWidget *parent = nullptr);

    TrayMenu *trayMenu() const;
    void setTrayMenu(TrayMenu *trayMenu);

signals:

public slots:
    void setToolTips(QString name,QString artist);

private:
    TrayMenu *m_trayMenu;

};

#endif // TRAY_H
