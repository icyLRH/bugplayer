#include "songs.h"

//Song's infomation

Songs::Songs(QString sname , QString sduration , QString sartist ,
             QString salbum , QString sstyle, QString splace)
{
    m_sname = sname;
    m_sduration = sduration;
    m_sartist = sartist;
    m_salbum = salbum;
    m_sstyle = sstyle;
    m_splace = splace;
}

Songs::Songs(QStringList list)
{
    m_sname = list[0];
    m_sduration = list[1];
    m_sartist = list[2];
    m_salbum = list[3];
    m_sstyle = list[4];
    m_splace = list[5];
}

QString Songs::sname() const
{
    return m_sname;
}

void Songs::setSname(const QString &sname)
{
    m_sname = sname;
}

QString Songs::sartist() const
{
    return m_sartist;
}

void Songs::setSartist(const QString &sartist)
{
    m_sartist = sartist;
}

QString Songs::sduration() const
{
    return m_sduration;
}

void Songs::setSduration(const QString &sduration)
{
    m_sduration = sduration;
}

QString Songs::splace() const
{
    return m_splace;
}

void Songs::setSplace(const QString &splace)
{
    m_splace = splace;
}

QString Songs::sstyle() const
{
    return m_sstyle;
}

void Songs::setSstyle(const QString &sstyle)
{
    m_sstyle = sstyle;
}

/*
 * Function Name: getsonglist.
 * Description: write song's information into a QStringList.
 * Created: 18/09/09
 * Parameter: VOID
 * Return Code: QStringList
 * Author: Icy
*/
QStringList Songs::getsonglist(void)
{
    QStringList list;
    list<<sname()<<sduration()<<sartist()<<salbum()<<sstyle()<<splace();
    return list;
}


QString Songs::salbum() const
{
    return m_salbum;
}

void Songs::setSalbum(const QString &salbum)
{
    m_salbum = salbum;
}
