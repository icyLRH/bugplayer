#ifndef FRAMEOFBOTTOM_H
#define FRAMEOFBOTTOM_H

#include <QWidget>
#include "customslider.h"
class QFrame;
class QPushButton;
class QLabel;
class QSlider;
class CustomSlider;

class FrameOfBottom : public QWidget
{
    Q_OBJECT
public:
    explicit FrameOfBottom(QWidget *parent = nullptr);

    QPushButton *previousTrackBtn() const;
    void setPreviousTrackBtn(QPushButton *previousTrackBtn);

    QPushButton *nextTrackBtn() const;
    void setNextTrackBtn(QPushButton *nextTrackBtn);

    QPushButton *playBtn() const;
    void setPlayBtn(QPushButton *playBtn);

    QLabel *time1Label() const;
    void setTime1Label(QLabel *time1Label);

    QLabel *time2Label() const;
    void setTime2Label(QLabel *time2Label);

    CustomSlider *timeBarSlider() const;
    void setTimeBarSlider(CustomSlider *timeBarSlider);

    QSlider *volumnSlider() const;
    void setVolumnSlider(QSlider *volumnSlider);

    QPushButton *lrcOpenBtn() const;
    void setLrcOpenBtn(QPushButton *lrcOpenBtn);

    QPushButton *modeBtn() const;
    void setModeBtn(QPushButton *modeBtn);

    void customStyleSheet();

signals:


public slots:


private:
    QPushButton *m_previousTrackBtn;
    QPushButton *m_nextTrackBtn;
    QPushButton *m_playBtn;
    QLabel *m_time1Label;
    QLabel *m_time2Label;
    CustomSlider *m_timeBarSlider;
    QSlider *m_volumnSlider;
    QPushButton *m_lrcOpenBtn;
    QPushButton *m_modeBtn;
};

#endif // FRAMEOFBUTTOM_H
