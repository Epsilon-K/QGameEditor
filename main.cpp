#include "qgameeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QGameEditor");
    a.setApplicationVersion("1.0");
    QGameEditor w;
    w.show();

    return a.exec();
}
