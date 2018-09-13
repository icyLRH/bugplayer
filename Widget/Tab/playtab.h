#ifndef PLAYTAB_H
#define PLAYTAB_H

#include <QTabBar>
#include <QTabWidget>

#include "defaulttab.h"
#include "artisttab.h"
#include "genretab.h"
#include "webtab.h"
#include "listtab.h"
#include "newtabbarofplaytab.h"
class PlayTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit PlayTab(QWidget *parent = nullptr);

    DefaultTab *defaultTab() const;
    void setDefaultTab(DefaultTab *defaultTab);

    ArtistTab *artistTab() const;
    void setArtistTab(ArtistTab *artistTab);

    GenreTab *genreTab() const;
    void setGenreTab(GenreTab *genreTab);

    DefaultTable *table() const;
    void setTable(DefaultTable *table);

    QWidget *lrcTab() const;
    void setLrcTab(QWidget *lrcTab);

    WebTab *webTab() const;
    void setWebTab(WebTab *webTab);

    ListTab *listTab() const;
    void setListTab(ListTab *listTab);

    int getLastIndex() const;
    void setLastIndex(int lastIndex);

    void resizeEvent(QResizeEvent *event);

signals:
    void freshOver(void);

    void resizeEventHappened(void);


public slots:
    void webSearched(void);

    void localSearched(QString text);

    void fresh(void);

    void getLogin(void);

    void changeIconFont(int index);

    void resetIconFont(int index);

private:
    DefaultTab *m_defaultTab;
    ArtistTab *m_artistTab;
    GenreTab *m_genreTab;
    WebTab *m_webTab;
    QWidget *m_lrcTab;
    ListTab *m_listTab;

    DefaultTable *m_table;      //a temp for connect

    int m_lastIndex;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
};


#endif // PLAYTAB_H
