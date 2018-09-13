#include "customtabstyle.h"


/*
 * Function Name: sizeFromContents
 * Description: change the default size and shape of every tab
 * Created: 18/09/09
 * Parameter: type QStyle::ContentsType
 *              option  const QStyleOption *
 *              size    const QSize &
 *              widget  const QWidget *
 * Return Code: QSize
 * Author: Granx
*/
QSize CustomTabStyle::sizeFromContents(QStyle::ContentsType type,
                                       const QStyleOption *option,
                                       const QSize &size,
                                       const QWidget *widget) const
{
    //first, get default value
    QSize newSize = QProxyStyle::sizeFromContents(type, option, size, widget);

    //if type is CT_TabBarTab
    if (type == QStyle::CT_TabBarTab)
    {
        //Swaps the width and height values.
        newSize.transpose();

        //set item size in tabBar
        newSize.rwidth() = 250;
        newSize.rheight() = 40;
    }
    return newSize;
}

/*
 * Function Name: drawControl
 * Description: custom draw control
 * Created: 18/09/09
 * Parameter: element QStyle::ControlElement
 *              option  const QStyleOption *
 *              painter    QPainter *
 *              widget  const QWidget *
 * Return Code: QSize
 * Author: Granx
*/
void CustomTabStyle::drawControl(QStyle::ControlElement element,
                                 const QStyleOption *option,
                                 QPainter *painter,
                                 const QWidget *widget) const
{
    //if element is CE_TabBarTabLabel ,then
    if (element == CE_TabBarTabLabel)
    {

        //force type conversion
        if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option))
        {
            QRect allRect = tab->rect;

            if (tab->state & QStyle::State_Selected)
            {
                //save painter
                painter->save();
                painter->setPen(0xffbbd3);
                painter->setBrush(QBrush(0xffbbd3));

                //adjusted
                painter->drawRect(allRect.adjusted(5,5,-5,-5));

                //restore painter
                painter->restore();
            }

            else if (tab->state & QStyle::State_MouseOver )
            {
                //save painter
                painter->save();
                painter->setPen(0xffe2ec);
                painter->setBrush(QBrush(0xffe2ec));

                //adjusted
                painter->drawRect(allRect.adjusted(5,5,-5,-5));

                //restore painter
                painter->restore();
            }
            else
            {}

            QTextOption option;
            option.setAlignment(Qt::AlignCenter);

            //set selected text color
            if (tab->state & QStyle::State_Selected)
            {
                painter->setPen(0xffffff);
            }
            else if (tab->state & QStyle::State_MouseOver)
            {
                painter->setPen(0x959595);
            }
            //set normal text color
            else
            {
                painter->setPen(QColor(84,84,84));
            }
            //drawText
            painter->drawText(allRect, tab->text, option);
            return;
        }
    }
    if (element == CE_TabBarTab)
    {
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
