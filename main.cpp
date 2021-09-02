#include "MainWindow.h"

#include <QApplication>
#include "windows.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    return a.exec();
}
