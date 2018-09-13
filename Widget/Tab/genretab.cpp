#include "genretab.h"
#include "customtabstyle.h"


GenreTab::GenreTab(QWidget *parent) : QTabWidget(parent)
{
    setTabPosition(QTabWidget::West);

    //set CustomTabStyle
    tabBar()->setStyle(new CustomTabStyle);

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
DefaultTable *GenreTab::addTab_(const QIcon &icon, const QString &name)
{
    //add dafaultTable
    DefaultTable *temp = new DefaultTable (this);
    addTab(temp,icon,name);

    //return the pointer just created
    return temp;
}

/*
 * Function Name: addTab_
 * Description: add tab without a widget parameter and return dynamical table pointer.
 * Created: 18/09/09
 * Parameter:name   const QString &
 * Return Code: DefaultTable *
 * Author: Granx
*/
DefaultTable *GenreTab::addTab_(const QString &name)
{
    DefaultTable *temp = new DefaultTable (this);
    addTab(temp,name);
    return temp;
}


