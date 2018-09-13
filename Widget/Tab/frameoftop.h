#ifndef FRAMEOFTOP_H
#define FRAMEOFTOP_H

#include <QWidget>
#include <QPoint>

class QFrame;
class QPushButton;
class QLabel;
class QSlider;
class QSplitter;
class QLineEdit;
class About;

class FrameOfTop : public QWidget
{
    Q_OBJECT
public:
    explicit FrameOfTop(QWidget *parent = nullptr);

    void customStylesSheet();

    QPushButton *optionBtn() const;
    void setOptionBtn(QPushButton *optionBtn);

    QLineEdit *searchEdit() const;
    void setSearchEdit(QLineEdit *searchEdit);

    QPushButton *skinBtn() const;
    void setSkinBtn(QPushButton *skinBtn);

    QPushButton *minimumBtn() const;
    void setMinimumBtn(QPushButton *minimumBtn);

    QPushButton *exitBtn() const;
    void setExitBtn(QPushButton *exitBtn);

    QPoint startPoint() const;
    void setStartPoint(const QPoint &startPoint);

    QPoint windowPoint() const;
    void setWindowPoint(const QPoint &windowPoint);

    bool isMove() const;
    void setIsMove(bool isMove);

    bool allowMove() const;
    void setAllowMove(bool allowMove);

    QPushButton *searchBtn() const;
    void setSearchBtn(QPushButton *searchBtn);

    QLineEdit *searchEdit2() const;
    void setSearchEdit2(QLineEdit *searchEdit2);

    QPushButton *searchBtn2() const;
    void setSearchBtn2(QPushButton *searchBtn2);

    About *about() const;
    void setAbout(About *about);

    QLabel *labelHorse() const;
    void setLabelHorse(QLabel *labelHorse);

    QString labelHorseString() const;
    void setLabelHorseString(const QString &labelHorseString);

    QString lastLabelHorseString() const;
    void setLastLabelHorseString(const QString &lastLabelHorseString);

    QTimer *getTimer() const;
    void setTimer(QTimer *timer);

    QPushButton *getSelectBtn() const;
    void setSelectBtn(QPushButton *selectBtn);

    QPushButton *getScanBtn() const;
    void setScanBtn(QPushButton *scanBtn);

    QPushButton *getUserBtn() const;
    void setUserBtn(QPushButton *userBtn);

signals:
    void sendText(QString);
    void sendText2(QString);

    void loging(void);

    void selected(void);

    void scaned(void);

    void skined(void);

public slots:
    void skinBtnPressed();
    void userBtnPressed();
    void exitBtnPressed();
    void minimumBtnPressed();

    void searchBtnPressed();
    void searchBtn2Pressed();

    void horseLabelGo();
    void getNameAndArtist(const QString name, const QString artist);

    void selectBtnPressed();
    void scanBtnPressed();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:

    QPushButton *m_optionBtn;

    QLabel *m_labelHorse;
    QString m_labelHorseString;
    QString m_lastLabelHorseString;
    QTimer *m_timer;
    int nPos;

    QLineEdit *m_searchEdit;
    QPushButton *m_searchBtn;
    QLineEdit *m_searchEdit2;
    QPushButton *m_searchBtn2;

    QPushButton *m_selectBtn;
    QPushButton *m_scanBtn;


    QPushButton *m_skinBtn;
    QPushButton *m_userBtn;
    QPushButton *m_minimumBtn;
    QPushButton *m_maxmumBtn;
    QPushButton *m_exitBtn;

    QPoint offset;

    About *m_about;

};

#endif // FRAMEOFTOP_H
