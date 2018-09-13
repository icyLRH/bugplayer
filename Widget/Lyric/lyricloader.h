#ifndef LYRICLOADER_H
#define LYRICLOADER_H

#include <QWidget>


//class of time-text
class LyricLine
{
public:
    LyricLine(int time,QString text):time(time),text(text)
    {

    }

    int time;
    QString text;


};


class LyricLoader: public QWidget
{
    Q_OBJECT
public:
    explicit LyricLoader(QWidget *parent = nullptr);

    bool processContent(const QString &content);

    int getLineByPosition(const int &ms,const int &startPos);

    QList<LyricLine *> mLines;      //store class of time-text
    bool mHasTimer;


signals:
    void lyricChanged(void);
};




#endif // LYRICLOADER_H
