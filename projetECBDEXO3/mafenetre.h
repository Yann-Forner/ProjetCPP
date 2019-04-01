#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include <stdio.h>
#include <iostream>
#include <QString>
#include <cstdlib>
#include <QTableWidget>
#include "charger_csv.h"



class MaFenetre : public QMainWindow
{
    Q_OBJECT
public slots :
    void setQuitter();
    void prediction();
    double frequence(string maladie);
    double conf(string symptome,string maladie,string valSymptome,double freq);
    int findCol(string symptome);
    vector <string> getMaladies();
    bool isPresent(string str ,  vector<string> VStr);
public :
    MaFenetre(QWidget *parent = 0);
private :
    QLineEdit *m_Nom,*m_Prenom;
    QLabel *m_lab, *m_tra, * m_1erAttrLab,*m_3emeAttrLab,*m_labelVallAttr,*m_labNom,*m_labPrenom,*m_labScore;
    QPushButton *m_bou,*m_bouPredict;
    QComboBox *m_com,*m_1erAttrCombo,*m_3emeAttrCombo;
    QString couleur;
    CVString m_vet;
    CMatString m_mat;
    QTableWidget *m_tab;
};
