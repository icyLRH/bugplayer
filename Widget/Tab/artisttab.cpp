#include <QStringList>
#include <QDebug>

#include "artisttab.h"
#include "customtabstyle.h"


ArtistTab::ArtistTab(QWidget *parent) : QTabWidget (parent)
{

    //add tabBar
    QTabBar *tabBar = new QTabBar (this);
    setTabBar(tabBar);
    tabBar->setUsesScrollButtons(2);

    //set tabBar position
    setTabPosition(QTabWidget::West);

    //set tabBar customTabStyle
    tabBar->setStyle(new CustomTabStyle);

    //uses style sheet to hide scroller and better performance
    setStyleSheet("QTabBar::scroller{width: 0px;}");

}

/*
 * Function Name: addTab_
 * Description: add tab without a widget parameter and return dynamical table pointer.
 * Created: 18/09/09
 * Parameter: icon  const QIcon &
 *            name  const QString &
 * Return Code: DefaultTable *
 * Author: Granx
*/
DefaultTable *ArtistTab::addTab_(const QIcon &icon, const QString &name)
{
    //add dafaultTable
    DefaultTable *table = new DefaultTable (this);
    addTab(table,icon,name);

    //return the pointer just created
    return table;
}

/*
 * Function Name: addTab_
 * Description: add tab without a widget parameter and return dynamical table pointer.
 * Created: 18/09/09
 * Parameter:name   const QString &
 * Return Code: DefaultTable *
 * Author: Granx
*/
DefaultTable *ArtistTab::addTab_(const QString &name)
{
    //add dafaultTable
    DefaultTable *table = new DefaultTable (this);
    addTab(table,name);

    //return the pointer just created
    return table;
}

