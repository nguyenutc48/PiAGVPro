#include "Application.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fuson");
    Application w;
    w.show();

    return a.exec();
}
