#ifndef GENRETAB_H
#define GENRETAB_H

#include <QTabWidget>
#include "defaulttable.h"

class GenreTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit GenreTab(QWidget *parent = nullptr);

    DefaultTable* addTab_(const QIcon &icon, const QString &name = "Genre");
    DefaultTable* addTab_(const QString &name = "Genre");

signals:

public slots:

private:
};

#endif // GENRETAB_H
