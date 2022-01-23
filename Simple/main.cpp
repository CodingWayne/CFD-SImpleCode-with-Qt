#include "simple.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Simple w;



    w.show();
    return a.exec();
}
