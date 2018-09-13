#ifndef TABLEMENU_H
#define TABLEMENU_H

#include <QWidget>
#include <QMenu>
#include <QAction>
class TableMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TableMenu(QWidget *parent = nullptr);

    void customStylesSheet(void);

    void customRemoveAction(int index);


    QAction *addToListTab() const;
    void setAddToListTab(QAction *addToListTab);

    QAction *flash() const;
    void setFlash(QAction *flash);

    QAction *deleteMusic() const;
    void setDeleteMusic(QAction *deleteMusic);

    QAction *addToDefaultTab() const;
    void setAddToDefaultTab(QAction *addToDefaultTab);

signals:   
    void addToListTabAction(void);

    void flashAction(void);

    void deleteMusicAction(void);

    void addToDefaultTabAction(void);

public slots:
    void emitAddToListTab(void);

    void emitFlash(void);

    void emitDeleteMusic(void);

    void emitAddToDefaultTab(void);

private:
    QAction* m_addToListTab;
    QAction* m_flash;
    QAction* m_deleteMusic;
    QAction* m_addToDefaultTab;
};

#endif // TABLEMENU_H
