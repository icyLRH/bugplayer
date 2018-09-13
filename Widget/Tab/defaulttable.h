#ifndef DEFAULTTABOFARTISTTAB_H
#define DEFAULTTABOFARTISTTAB_H

#include <QTableWidget>
#include "tablemenu.h"

class DefaultTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit DefaultTable(QWidget *parent = nullptr);

    void addItem(const QStringList stringList);

    void customStyleSheet();    
    void setRowColor(int row, QColor rowColor, QColor textColor);

    TableMenu *tableMenu() const;
    void setTableMenu(TableMenu *tableMenu);

signals:
    void sendUrl(QString url);    
    void sendItems(QList<QTableWidgetItem *>);

    void deleteOver(void);

public slots:
    void sort(int column);

    void emitsendItemsList();

    virtual void deleteMusic(void);

    void customCellEntered(int row, int column);


protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    TableMenu* m_tableMenu;

};


#endif // DEFAULTTABOFARTISTTAB_H
