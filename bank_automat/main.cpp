#include "kortinlukija.h"
#include "bankwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    KortinLukija w;
    w.show();
    return a.exec();
}
