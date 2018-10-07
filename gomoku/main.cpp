#include "mainwindow.h"
#include "board.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(930,800);
    w.setWindowTitle(QObject::tr("GoMoKu"));
    w.show();

    return a.exec();
}
