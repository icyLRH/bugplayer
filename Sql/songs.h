#ifndef SONGS_H
#define SONGS_H
#include <QString>
#include <QStringList>

//歌曲类，包括文件路径、名称、时长、演唱者、流派

class Songs
{
public:
    Songs(QString sname = NULL,QString sduration = NULL,QString sartist = NULL,
          QString salbum = NULL,QString sstyle = NULL,QString splace = NULL);

    Songs(QStringList list);

    QString splace() const;
    void setSplace(const QString &splace);

    QString sname() const;
    void setSname(const QString &sname);

    QString sduration() const;
    void setSduration(const QString &sduration);

    QString sartist() const;
    void setSartist(const QString &sartist);

    QString salbum() const;
    void setSalbum(const QString &salbum);

    QString sstyle() const;
    void setSstyle(const QString &sstyle);

    QStringList getsonglist(void);

    Songs & operator =(const Songs& so)//赋值运算符
    {
        m_splace = so.splace();
        m_sname = so.sname();
        m_sduration = so.sduration();
        m_sartist = so.sartist();
        m_sstyle = so.sstyle(); 
        m_salbum = so.salbum();
        return *this;
    }


private:
    QString m_sname;
    QString m_sduration;
    QString m_sartist;
    QString m_salbum;
    QString m_sstyle;
    QString m_splace;
};

#endif // SONGS_H
