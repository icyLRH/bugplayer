#include "lyricloader.h"

#include <QString>
#include <QList>
#include <QDebug>

LyricLoader::LyricLoader(QWidget *parent) :QWidget(parent)
{

}

/*按照维基百科的说明，标准的LRC格式歌词，每一行开头都有一个形如[mm:ss.xx]形式的时间标签，
实际上有的歌词每一行开头可能有多个时间标签，表示这一句可能会在不同时间点重复多次。
以此为标准，实现解析的思路如下：

1.查找第一个形如[mm:ss.xx]的时间标签。
          如果找不到，就把文本按照换行符简单分割，完成解析；
          找到的话就记录标签的位置并执行步骤2。
2.查找下一个时间标签的位置。
          如果找不到，就把最后一个时间标签之后的全部文本作为最后一句歌词，保存到结果中，执行步骤4；
          找到的话就记录标签的位置并执行步骤3。
3.比较当前标签和上一个标签的位置。
          如果是紧挨的话，表示这两个标签代表同一句歌词，重复步骤2；
          如果不是紧挨的，就把两个标签之间的文本作为歌词保存到结果中，然后重复步骤2。
4.把得到的结果按照时间顺序重新排列，完成解析。

每一行歌词都可以抽象为一个包含时间和文本的结构体，解析的结果使用QList维护

时间 - 歌词的抽象结构体

注意这个函数
*/

/*
 * Function Name: lyricTimeLessThan
 * Description: compare ready
 * Created: 18/09/09
 * Parameter:  line1    const LyricLine *
 *              line2    const LyricLine *
 * Return Code: bool
 * Author: Granx
*/
bool lyricTimeLessThan(const LyricLine *line1, const LyricLine *line2)
{
    return line1->time < line2->time;
}

/*
 * Function Name: processContent
 * Description: process lyric
 * Created: 18/09/09
 * Parameter:  content  const QString &
 * Return Code: bool
 * Author: Granx
*/
bool LyricLoader::processContent(const QString &content)
{
    qDebug()<<"process action";
    if(!mLines.isEmpty())
    {
        qDebug()<<"mLines isn't empty 1";
        qDeleteAll(mLines);

        mLines.clear();

        mHasTimer = false;

        //inform lyric has changed, must search from first
        emit lyricChanged();
    }

    //search for time label in lrc
    const QRegExp rx("\\[(\\d+):(\\d+(\\.\\d+)?)\\]");

    //1
    int pos = rx.indexIn(content);
    qDebug()<<"pos go";
    if(pos == -1)   //no match
    {
        qDebug()<<"pos == -1";
        QStringList list = content.split('\n', QString::SkipEmptyParts);
        foreach (QString line,list)
        {
            mLines.append(new LyricLine(0,line));

        }

        mHasTimer = false;
    }
    else
    {
        int lastPos;
        QList<int> timeLabels;
        do
        {
            //2
            timeLabels << (rx.cap(1).toInt() * 60 + rx.cap(2).toDouble()) * 1000;

            lastPos = pos + rx.matchedLength();

            pos = rx.indexIn(content, lastPos);
            if (pos == -1) {
                QString text = content.mid(lastPos).trimmed();
                foreach (const int& time, timeLabels)
                    mLines.append(new LyricLine(time, text));
                break;
            }
            // 3

            //get text between lastpos, pos - lastPos
            QString text = content.mid(lastPos, pos - lastPos);
            if (!text.isEmpty()) {
                foreach (const int& time, timeLabels)
                    mLines.append(new LyricLine(time, text.trimmed()));
                timeLabels.clear();
            }
        }
        while (true);
        qDebug()<<"do out";
        //4
        qStableSort(mLines.begin(), mLines.end(),lyricTimeLessThan);

        mHasTimer = true;
    }

    if(!mLines.isEmpty())
    {
        qDebug()<<"mLines isn't empty 2";

        //inform lyric has changed, must search from first
        emit lyricChanged();
        return true;
    }

    return false;
}

/*
 * Function Name: getLineByPosition
 * Description: get line text by current ms, search begin at startPos
 * Created: 18/09/09
 * Parameter:  ms  const int &
 *              startPos    const int &
 * Return Code: int
 * Author: Granx
*/
int LyricLoader::getLineByPosition(const int &ms, const int &startPos)
{
    if(!mHasTimer || mLines.isEmpty())
        return -1;

    int result = qBound(0, startPos, mLines.size());
    while (result < mLines.size())
    {
        if(mLines.at(result)->time > ms)
        {
            break;
        }
        result++;
    }
    return result - 1;
}




