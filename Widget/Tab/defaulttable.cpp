#include <QDebug>
#include <QStringList>
#include <QAbstractItemView>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QHeaderView>
#include <QModelIndexList>
#include <QScrollBar>
#include "songsdata.h"
#include "defaulttable.h"


DefaultTable::DefaultTable(QWidget *parent) : QTableWidget(parent)
{
    //tableMenu
    setTableMenu(new TableMenu (this));

    //column
    setColumnCount(6);

    //headerLabels
    setHorizontalHeaderLabels(QStringList()<<"名称"<<"时长"<<"艺术家"<<"专辑"<<"流派"<<"Url");

    //noFrame
    setFrameShape(QFrame::NoFrame);

    //noGrid
    setShowGrid(false);

    //lastSection stretch
    horizontalHeader()->setStretchLastSection(true);

    //selection a row
    setSelectionBehavior(QAbstractItemView::SelectRows);

    //no edit
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    //extend selection
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    //hide verticalHeader
    verticalHeader()->setVisible(false);

    //scrollMode
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    //repair
    horizontalHeader()->setHighlightSections(false);

    //set width
    horizontalHeader()->resizeSections(QHeaderView::Interactive);
    horizontalHeader()->resizeSection(0,250);
    horizontalHeader()->resizeSection(1,70);
    horizontalHeader()->resizeSection(2,200);
    horizontalHeader()->resizeSection(3,250);
    horizontalHeader()->resizeSection(4,70);

    //connect sctionClicked to achieve sort ascend or descend
    connect(horizontalHeader(),&QHeaderView::sectionClicked,this,&DefaultTable::sort);

    //send ItemsList (musics) for listTab to add
    connect(tableMenu(),&TableMenu::addToListTabAction,this,&DefaultTable::emitsendItemsList);

    //delete seleted musics
    connect(tableMenu(),&TableMenu::deleteMusicAction,this,&DefaultTable::deleteMusic);
    
    //set style sheet
    customStyleSheet();

    //no delegate
    setFocusPolicy(Qt::NoFocus);

    //customCellEnter to achieve hover
    setMouseTracking(true);
    connect(this,&DefaultTable::cellEntered,this,&DefaultTable::customCellEntered);

}

/*
 * Function Name: customCellEntered
 * Description: change the row color, hover
 * Created: 18/09/09
 * Parameter: row int
 *            column  int
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::customCellEntered(int row, int column)
{
    static int previousColorRow = -1;

    QTableWidgetItem *tempItem = 0;

    //reset color pre row
    tempItem = item(previousColorRow,0);
    if(tempItem != 0)
    {
        setRowColor(previousColorRow, QColor(250,250,250), QColor(84,84,84));
    }

    //set current row
    tempItem = item(row, column);
    if(tempItem != 0 && !tempItem->isSelected() && !tempItem->text().isEmpty())
    {
        setRowColor(row, QColor(255,226,236), QColor(149,149,149));
    }

    //update pre row
    previousColorRow = row;
}

/*
 * Function Name: setRowColor
 * Description: row color, hover
 * Created: 18/09/09
 * Parameter: row int
 *            rowColor  QColor
 *            textColor  QColor
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::setRowColor(int row, QColor rowColor, QColor textColor)
{
    for(int i = 0; i < columnCount(); i++)
    {
        item(row, i)->setBackgroundColor(rowColor);
        item(row, i)->setTextColor(textColor);
    }
}

/*
 * Function Name: addItem
 * Description: addItem by stringList.
 * Created: 18/09/09
 * Parameter: stringList  const QStringList
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::addItem(const QStringList stringList)
{
    int row = rowCount();
    insertRow(row);
    for(int i = 0; i<stringList.size(); i++)
    {
        //start from (0,0)
        setItem(row, i, new QTableWidgetItem(stringList.at(i)));
    }
}

/*
 * Function Name: sort
 * Description: achieve to sort
 * Created: 18/09/09
 * Parameter: column int
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::sort(int column)
{
    static int flag = 0;
    if(flag % 2 == 0)
    {
        sortItems(column,Qt::AscendingOrder);
        flag++;
    }
    else
    {
        sortItems(column,Qt::DescendingOrder);
        flag++;
    }
}

/*
 * Function Name: emitsendItemsList
 * Description: get all rows index, send all Items by row
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::emitsendItemsList()
{
    //no items selected, return
    if(selectedItems().isEmpty())
    {
        return;
    }

    //all selected songs

    //store all rows index
    QItemSelectionModel *selections = selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap <int, int> rowMap;
    foreach (QModelIndex index, selected)
    {
        rowMap.insert(index.row(), 0);
    }

    //get all row index, emit content
    QMap<int,int>::iterator it;
    for(it = rowMap.begin(); it != rowMap.end(); ++it)
    {
        QList<QTableWidgetItem*>items;
        for(int i = 0; i < columnCount(); i++)
        {
            items<<item(it.key(),i);
        }
        emit sendItems(items);
        items.clear();
    }
}

/*
 * Function Name: deleteMusic
 * Description: deleteMusic in database, then refresh
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::deleteMusic()
{
    //no items selected, return
    if(selectedItems().isEmpty())
    {
        return;
    }

    //all selected songs

    //store all rows index
    QItemSelectionModel *selections = selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap <int, int> rowMap;
    foreach (QModelIndex index, selected)
    {
        rowMap.insert(index.row(), 0);
    }

    //get all row index, emit content
    QMap<int,int>::iterator it;
    for(it = rowMap.begin(); it != rowMap.end(); ++it)
    {
        QList<QTableWidgetItem*>items;
        for(int i = 0; i < columnCount(); i++)
        {
            items<<item(it.key(),i);
        }
//        emit sendItems(items);


        //SQL
        SongsData songsData;
        songsData.deleteSong(items.at(items.size() - 1)->data(Qt::DisplayRole).toString());

        items.clear();
    }


    //inform playTab to refresh, which will emit signal to inform others
    emit deleteOver();

}


/*
 * Function Name: mouseDoubleClickEvent
 * Description: override mouseDoubleClickEvent, achieves play a music by doubleClick that.
 * Created: 18/09/09
 * Parameter: event QMouseEvent*
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    //check size
    QList<QTableWidgetItem *> Items =selectedItems();
    if(Items.size()!= 6)
    {
        return;
    }

    QTableWidgetItem *urlItem;
    urlItem = Items.at(Items.size()-1);

    QString url = urlItem->data(Qt::DisplayRole).toString();

    //sendItems to listTab
    emit sendItems(Items);

    //url to newPlayer
    emit sendUrl(url);

    event->accept();

}

/*
 * Function Name: mousePressEvent
 * Description: override mousePressEvent, show menu.
 * Created: 18/09/09
 * Parameter: event QMouseEvent*
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::RightButton)
    {
        QPoint point = event->globalPos();
        tableMenu()->popup(point);
    }
    QTableWidget::mousePressEvent(event);
}

void DefaultTable::mouseReleaseEvent(QMouseEvent *event)
{
    QTableWidget::mouseReleaseEvent(event);
}

TableMenu *DefaultTable::tableMenu() const
{
    return m_tableMenu;
}

void DefaultTable::setTableMenu(TableMenu *tableMenu)
{
    m_tableMenu = tableMenu;
}

/*
 * Function Name: customStyleSheet
 * Description: set styles sheet
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: VOID
 * Author: Granx
*/
void DefaultTable::customStyleSheet()
{
    setStyleSheet("QTableWidget{selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 0,stop: 0 #ffbbd3, stop: 1 #37afff);"
                  "selection-color: white;"
                  "background-color:rgb(250,250,250);"
                  "color:rgb(84,84,84);"
                  "border: 0px;}");

    horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{height:10px;background:transparent;background-color:rgb(248, 248, 248);margin:0px,0px,0px,0px;padding-left:10px;padding-right:10px;}"
                                         "QScrollBar::handle:horizontal{height:10px;background:lightgray;border-radius:5px;/*min-height:20;*/}"
                                         "QScrollBar::handle:horizontal:hover{height:10px;background:gray;border-radius:5px;/*min-height:20;*/}"
                                         "QScrollBar::add-line:horizontal{/*height:10px;width:10px;*/border-image:url(:/button/images/button/right.png);/*subcontrol-position:right;*/}"
                                         "QScrollBar::sub-line:horizontal{/*height:10px;width:10px;*/border-image:url(:/button/images/button/left.png);/*subcontrol-position:left;*/}"
                                         "QScrollBar::add-line:horizontal:hover{/*height:10px;width:10px;*/border-image:url(:/button/images/button/right_mouseDown.png);/*subcontrol-position:right;*/}"
                                         "QScrollBar::sub-line:horizontal:hover{/*height:10px;width:10px;*/border-image:url(:/button/images/button/left_mouseDown.png);/*subcontrol-position:left;*/}"
                                         "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal{background:transparent;border-radius:5px;}");
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical{width:10px;background:transparent;background-color:rgb(248, 248, 248);margin:0px,0px,0px,0px;padding-top:10px;padding-bottom:10px;}"
                                       "QScrollBar::handle:vertical{width:10px;background:lightgray ;border-radius:5px;min-height:20px;}"
                                       "QScrollBar::handle:vertical:hover{width:10px;background:gray;border-radius:5px;min-height:20px;}"
                                       "QScrollBar::add-line:vertical{height:10px;width:10px;border-image:url(:/button/images/button/down.png);subcontrol-position:bottom;}"
                                       "QScrollBar::sub-line:vertical{height:10px;width:10px;border-image:url(:/button/images/button/up.png);subcontrol-position:top;}"
                                       "QScrollBar::add-line:vertical:hover{height:10px;width:10px;border-image:url(:/button/images/button/down_mouseDown.png);subcontrol-position:bottom;}"
                                       "QScrollBar::sub-line:vertical:hover{height:10px;width:10px;border-image:url(:/button/images/button/up_mouseDown.png);subcontrol-position:top;}"
                                       "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent;border-radius:5px;}");


}


