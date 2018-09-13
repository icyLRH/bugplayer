#include "tray.h"


Tray::Tray(QWidget *parent) : QSystemTrayIcon(parent),
    m_trayMenu(new TrayMenu (parent))
{
    setToolTip("BugPlayer");

    QIcon icon (":/Icon/src/Icon/BugPlayer.png");
    setIcon(icon);

    setContextMenu(trayMenu());

    //显示图标
    show();
}

TrayMenu *Tray::trayMenu() const
{
    return m_trayMenu;
}

void Tray::setTrayMenu(TrayMenu *trayMenu)
{
    m_trayMenu = trayMenu;
}

/*
 * Function Name: setToolTips
 * Description: get name and artist, set tool tip
 * Created: 18/09/09
 * Parameter: name  QString
 * Return Code: VOID
 * Author: Granx
*/
void Tray::setToolTips(QString name, QString artist)
{
    setToolTip(name + "-" + artist);
}


