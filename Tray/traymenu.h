#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QMenu>

class QLabel;
class QAction;

class TrayMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TrayMenu(QWidget *parent = nullptr);

    void creatActions();

    void customStylesSheet(void);

    QAction *play() const;
    void setPlay(QAction *play);

    QAction *previous() const;
    void setPrevious(QAction *previous);

    QAction *next() const;
    void setNext(QAction *next);

    QMenu *modeMenu() const;
    void setModeMenu(QMenu *modeMenu);

    QAction *single() const;
    void setSingle(QAction *single);

    QAction *order() const;
    void setOrder(QAction *order);

    QAction *rand() const;
    void setRand(QAction *rand);

    QAction *openLrc() const;
    void setOpenLrc(QAction *openLrc);

    QAction *lockLrc() const;
    void setLockLrc(QAction *lockLrc);

    QAction *options() const;
    void setOptions(QAction *options);

    QAction *exit() const;
    void setExit(QAction *exit);

signals:
    void playAction(void);
    void PreAction(void);
    void nextAction(void);

    void singleAction(void);
    void orderAction(void);
    void randAction(void);

    void openLrcAction(void);
    void lockLrcAction(void);
    void optionsAction(void);

public slots:

private:
    QAction *m_play;
    QAction *m_previous;
    QAction *m_next;

    QMenu *m_modeMenu;
    QAction *m_single;
    QAction *m_order;
    QAction *m_rand;

    QAction *m_openLrc;
    QAction *m_lockLrc;
    QAction *m_options;
    QAction *m_exit;
};

#endif // TRAYMENU_H
