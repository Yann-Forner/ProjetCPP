#include <QApplication>
#include "mafenetre.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    mafenetre fenetre;
    fenetre.show();
    return app.exec();
}
