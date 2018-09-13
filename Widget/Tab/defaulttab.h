#ifndef DEFAULTTAB_H
#define DEFAULTTAB_H

#include "defaulttable.h"
#include <QList>
#include <QTableWidgetItem>

class DefaultTab : public DefaultTable
{
    Q_OBJECT
public:
    explicit DefaultTab(QWidget *parent = nullptr);

signals:
    void fresh(void);

public slots:
    void flash(void); 
    void select(void);    
    void scan(void);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
};

#endif // DEFAULTTAB_H
