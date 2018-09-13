#include "newtabbarofplaytab.h"


NewTabBarOfPlayTab::NewTabBarOfPlayTab(PlayTab *parent)
    :QTabBar(parent)
{
    tempParent = parent;
    connect(tempParent,&PlayTab::resizeEventHappened,this,&NewTabBarOfPlayTab::windowChanged);

    setStyleSheet("QTabBar::tab{  background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                  "stop: 0 #F4F4F4, stop: 0.4 #EFEFEF,"
                  "stop: 0.5 #ECECEC, stop: 1.0 #E6E6E6);"
                  "border: 2px solid #C4C4C3;"
                  "border-bottom-color: #C2C7CB;"
                  "border-top-left-radius: 4px;"
                  "border-top-right-radius: 4px;"
                  "min-width: 8ex;"
                  "padding: 2px;"
                  "font-family: Microsoft YaHei;"
                  "font-size: 15px;}"
                  "QTabBar::tab:selected,QTabBar::tab:hover{"
                  "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                  "stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
                  "stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
                  "font-family: Microsoft YaHei;"
                  "font-size: 18px;}"
                  "QTabBar::tab:selected {"
                  "border-color: #9B9B9B;"
                  "border-bottom-color: #C2C7CB;}");
}

/*
 * Function Name: tabSizeHint
 * Description: override sizeHint
 * Created: 18/09/09
 * Parameter: index int
 * Return Code: QSize
 * Author: Granx
*/
QSize NewTabBarOfPlayTab::tabSizeHint(int index) const
{
    if(index != -1)
    {
        return QSize(((parentWidget()->width()))/tempParent->count(),40);
    }
    return QSize();
}

/*
 * Function Name: windowChanged
 * Description: as a slot, auto change width to adjust window's width
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void NewTabBarOfPlayTab::windowChanged()
{
    resize(parentWidget()->width()/tempParent->count(),40);
}
