#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T14:18:45
#
#-------------------------------------------------

QT       += core gui multimedia xml sql
RC_ICONS = BugPlayer0.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BugPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Network/lyricdownload.cpp \
    Network/network.cpp \
    Player/customslider.cpp \
    Player/newplayer.cpp \
    Player/player.cpp \
    Sql/namepassworddata.cpp \
    Sql/playlistdata.cpp \
    Sql/songs.cpp \
    Sql/songsdata.cpp \
    Tray/tray.cpp \
    Tray/traymenu.cpp \
    Widget/Bottom/frameofbottom.cpp \
    Widget/Lyric/lyric.cpp \
    Widget/Lyric/lyricdialog.cpp \
    Widget/Lyric/lyriclabel.cpp \
    Widget/Lyric/lyricloader.cpp \
    Widget/Tab/artisttab.cpp \
    Widget/Tab/customtabstyle.cpp \
    Widget/Tab/defaulttab.cpp \
    Widget/Tab/defaulttable.cpp \
    Widget/Tab/frameoftop.cpp \
    Widget/Tab/genretab.cpp \
    Widget/Tab/listtab.cpp \
    Widget/Tab/newtabbarofplaytab.cpp \
    Widget/Tab/playtab.cpp \
    Widget/Tab/tablemenu.cpp \
    Widget/Tab/webtab.cpp \
    Widget/Top/about.cpp \
    Widget/Top/checkinmainwindow.cpp \
    Widget/Top/signupdialog.cpp \
    Widget/Top/skin.cpp \
    Widget/Top/skinlabel.cpp

HEADERS += \
    Network/lyricdownload.h \
    Network/network.h \
    Player/customslider.h \
    Player/newplayer.h \
    Player/player.h \
    Sql/namepassworddata.h \
    Sql/playlistdata.h \
    Sql/songs.h \
    Sql/songsdata.h \
    Tray/tray.h \
    Tray/traymenu.h \
    Widget/Bottom/frameofbottom.h \
    Widget/Lyric/lyric.h \
    Widget/Lyric/lyricdialog.h \
    Widget/Lyric/lyriclabel.h \
    Widget/Lyric/lyricloader.h \
    Widget/Tab/artisttab.h \
    Widget/Tab/customtabstyle.h \
    Widget/Tab/defaulttab.h \
    Widget/Tab/defaulttable.h \
    Widget/Tab/frameoftop.h \
    Widget/Tab/genretab.h \
    Widget/Tab/listtab.h \
    Widget/Tab/newtabbarofplaytab.h \
    Widget/Tab/playtab.h \
    Widget/Tab/tablemenu.h \
    Widget/Tab/webtab.h \
    Widget/Top/about.h \
    Widget/Top/checkinmainwindow.h \
    Widget/Top/signupdialog.h \
    Widget/Top/skin.h \
    Widget/Top/skinlabel.h

win32: LIBS += -L$$PWD/taglib/ -llibtag.dll

INCLUDEPATH += $$PWD/taglib
INCLUDEPATH += $$PWD/Network
INCLUDEPATH += $$PWD/Player
INCLUDEPATH += $$PWD/Sql
INCLUDEPATH += $$PWD/Tray
INCLUDEPATH += $$PWD/Widget
INCLUDEPATH += $$PWD/Widget/Bottom
INCLUDEPATH += $$PWD/Widget/Lyric
INCLUDEPATH += $$PWD/Widget/Tab
INCLUDEPATH += $$PWD/Widget/Top

DEPENDPATH += $$PWD/taglib
DEPENDPATH += $$PWD/Network
DEPENDPATH += $$PWD/Player
DEPENDPATH += $$PWD/Sql
DEPENDPATH += $$PWD/Tray
DEPENDPATH += $$PWD/Widget
DEPENDPATH += $$PWD/Widget/Bottom
DEPENDPATH += $$PWD/Widget/Lyric
DEPENDPATH += $$PWD/Widget/Tab
DEPENDPATH += $$PWD/Widget/Top

RESOURCES += \
    src.qrc

FORMS += \
    Widget/Top/checkinmainwindow.ui \
    Widget/Top/signupdialog.ui
