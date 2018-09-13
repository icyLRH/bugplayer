#include "namepassworddata.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>


//name of database
const QString gDatabaseName = "namepassworddata.db";
//name of connetion
const QString gConnectionName = "nameConnection";

NamePasswordData::NamePasswordData(QWidget *parent):QWidget(parent)
{
    //judge whether the database has already been created
    bool isDatabaseExist = QFile::exists(gDatabaseName);
    //if not created
    if (!isDatabaseExist)
    {
        //creat a database
        db= QSqlDatabase::addDatabase("QSQLITE", gConnectionName);
        db.setDatabaseName(gDatabaseName);
        db.open();

        //creat songs table
        QSqlQuery sql_query1(db);
        QString create_sql =
               QString("create table if not exists userinfo (name varchar(30) primary key, password varchar(30));");

        //judge whether the creation is successful
        if(!sql_query1.exec(create_sql))
        {
            qDebug() << "Error: Fail to create table." << sql_query1.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
    }
    //creat connection
    else
    {
        //judge if the connection has already been exist.
        if (QSqlDatabase::contains(gConnectionName))
        {
            db = QSqlDatabase::database(gConnectionName);
        }
        else
        {
            db= QSqlDatabase::addDatabase("QSQLITE", gConnectionName);
            db.setDatabaseName(gDatabaseName);
        }
    }
}

/*
 * Function Name: checkUser.
 * Description: check the username and password.
 * Created: 18/09/09
 * Parameter: name QString
 *            password QString
 * Return Code: Bool
 * Author: Icy
*/
bool NamePasswordData::checkUser(QString name, QString password)
{
    if (!db.open())                                     //打开数据
    {
        return false;
    }
    else
    {}
    //selection
    QString sql = QString("select * from userinfo where name = '%1';").arg(name);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return false;
    }
    else
    {}

    if(query.next())
    {
        QString pass = query.value(1).toString();
        if (password == pass)
        {
            return true;
        }
        else
        {
            emit message("wrong password");
            qDebug()<<"密码错误";
            return false;
        }
    }
    else
    {
        emit message("User does not exist.");
        qDebug()<<"没有这个用户";
        return false;
    }
    db.close();                                      // 关闭数据库
}

/*
 * Function Name: insertinfo.
 * Description: insert name and password when sign up.
 * Created: 18/09/09
 * Parameter: name QString
 *            password QString
 * Return Code: Bool
 * Author: Icy
*/
bool NamePasswordData::insertinfo(QString name, QString password)
{
    if (!db.open())
    {
        return false;
    }
    else
    {}
    //insertation
    db.open();
    QString sql = QString("insert into userinfo (name, password) ");
    sql+=QString("values('%1', '%2');").arg(name).arg(password);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "insert fail:"
                 << query.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "insert success";
    }

    db.close();
    return true;
}

/*
 * Function Name: isin.
 * Description: judge if the username has already exist in database.
 * Created: 18/09/09
 * Parameter: name QString
 * Return Code: Bool
 * Author: Icy
*/
bool NamePasswordData::isin(QString name)
{
    if (!db.open())
    {
        qDebug()<<"fail";
        return false;
    }
    //selection
    QString sql = QString("select * from userinfo where name = '%1';").arg(name);
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qDebug() << "selete fail:"
                 << query.lastError().text();
        return false;
    }

    if(query.next())
    {
        qDebug()<<"已存在";
        return false;
    }
    else
    {
        qDebug()<<"还未存在";
        return true;
    }
    db.close();
}
