#include <QApplication>
#include "mainwindow.h"

#include "doctest.h"

int main(int argc, char *argv[])
{
    doctest::Context context;
    int res = context.run();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
