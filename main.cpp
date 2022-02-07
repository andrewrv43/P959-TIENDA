#include "tienda.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator traduccion;
    if (QLocale::system().language() == QLocale::English){
        traduccion.load(":/Tienda_en.qm");
    }
    else if(QLocale::system().language()==QLocale::German){
        traduccion.load(":/Tienda_de.qm");
    }

    a.installTranslator(&traduccion);
    Tienda w;
    w.show();
    return a.exec();
}
