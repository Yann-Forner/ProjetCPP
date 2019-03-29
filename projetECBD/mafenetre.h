#include <QWidget>
#include <QLabel>
#include <QPushButton>
class mafenetre : public QWidget
{
    Q_OBJECT
public slots :
    void setQuitter();
public :
    mafenetre();
private :
    QLabel *m_lab;
    QPushButton *m_bou;
};


