#ifndef NEWTABBAROFPLAYTAB_H
#define NEWTABBAROFPLAYTAB_H

#include "playtab.h"

class PlayTab;
class NewTabBarOfPlayTab : public QTabBar
{
    Q_OBJECT
public:
    PlayTab *tempParent;
    explicit NewTabBarOfPlayTab(PlayTab *parent = nullptr);

    QSize tabSizeHint(int index) const;

signals:

public slots:
    void windowChanged(void);

};
#endif // NEWTABBAROFPLAYTAB_H
