#include "gui_psd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui_psd w;
    w.show();
    return a.exec();
}
