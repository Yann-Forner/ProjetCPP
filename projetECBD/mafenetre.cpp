#include "mafenetre.h"
mafenetre::mafenetre() : QWidget()
{
    setFixedSize(800,600);
    m_lab = new QLabel (
                "Vive le module ECBD!", this);
    m_lab->setFont(QFont("Helvetica",
                         20, QFont::Bold, true));
    m_lab->move(100, 200);
    m_bou = new QPushButton(
                "Quitter", this);
    m_bou->setGeometry(600,400,80,40);
    connect(m_bou, SIGNAL(clicked()),
    this, SLOT(setQuitter()));

}

void mafenetre::setQuitter(){
    exit(0);
}
