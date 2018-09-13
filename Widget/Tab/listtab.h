#ifndef LISTTAB_H
#define LISTTAB_H

#include "defaulttable.h"
#include <QMediaPlaylist>
class ListTab : public DefaultTable
{
    Q_OBJECT
public:
    explicit ListTab(QWidget *parent = nullptr);

    QMediaPlaylist *Playlist() const;
    void setPlaylist(QMediaPlaylist *playlist);

signals:
    void sendUrlList(QStringList);
    void flashOver(void);
    void nameAndArtist(QString,QString);
    void sendIndex(int);

public slots:
    void getItems(const QList<QTableWidgetItem *> items);
    void flash();
    void emitName(int index);
    void deleteMusic();
    void freshAfterDelete(void);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QMediaPlaylist *m_playlist;

};

#endif // LISTTAB_H
