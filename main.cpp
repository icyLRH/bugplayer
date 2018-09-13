#include"newplayer.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewPlayer w;
    w.show();

    return a.exec();
}
