#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QComboBox>

class MaFenetre : public QMainWindow
{
    Q_OBJECT
public slots :
void setQuitter();
void setCouleur();
public :
MaFenetre(QWidget *parent = 0);
private :
QLabel *m_lab, *m_tra;
QPushButton *m_bou;
QComboBox *m_com;
QString couleur;
};
