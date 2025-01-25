#include "PhoneBill.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhoneBill AppMainWindow;
    AppMainWindow.show();
    return a.exec();
}
