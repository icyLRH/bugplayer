#ifndef NAMEPASSWORDDATA_H
#define NAMEPASSWORDDATA_H
#include <QString>
#include <QSqlDatabase>
#include<QWidget>


class NamePasswordData:public QWidget
{
    Q_OBJECT
public:
    NamePasswordData(QWidget *parent = 0);
    bool checkUser(QString name, QString password);
    bool insertinfo(QString name, QString password);
    bool isin(QString name);

signals:
    void message(QString);

private:
    QSqlDatabase db;
};

#endif // NAMEPASSWORDDATA_H
