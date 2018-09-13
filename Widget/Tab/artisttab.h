#ifndef ARTISTTAB_H
#define ARTISTTAB_H

#include <QTabWidget>
#include <QTabBar>
#include "defaulttable.h"


class ArtistTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit ArtistTab(QWidget *parent = nullptr);

    DefaultTable* addTab_(const QIcon &icon, const QString &name = "Artists");
    DefaultTable* addTab_(const QString &name = "Artists");

signals:

public slots:

};



#endif // ARTISTTAB_H
