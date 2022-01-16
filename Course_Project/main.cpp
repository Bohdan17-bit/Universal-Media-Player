#include "mainwindow.h"
#include "pathfiles.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/images/laptop_icon.png"));
    w.show();
    return a.exec();
}
