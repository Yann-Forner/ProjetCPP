#include "mafenetre.h"
MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{

    read_csv (m_mat, m_vet, "data.csv");


    setFixedSize(800,600);
    m_bou = new QPushButton("Quitter", this);




    //1er Atrribut
    m_1erAttrLab = new QLabel("Fièvre",this);
    m_1erAttrLab->setFont(QFont("Arial",12,QFont::Bold,true));
    m_1erAttrLab->move(200,200);
    m_1erAttrCombo = new QComboBox(this);
    m_1erAttrCombo->setGeometry(180,225,100,30);
    m_1erAttrCombo->addItem("NULL");
    m_1erAttrCombo->addItem("Oui");
    m_1erAttrCombo->addItem("Non");

    //2emeAttribut
    m_lab = new QLabel("Douleur", this);
    m_lab->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_lab->move(320, 200);
    m_com = new QComboBox(this);
    m_com->setGeometry(300,225,100,30);
    m_com->addItem("NULL");
    m_com->addItem("Abdomen");
    m_com->addItem("Gorge");
    m_com->addItem("Non");

    //3emeAttribut
    m_3emeAttrLab = new QLabel("Toux",this);
    m_3emeAttrLab->setFont(QFont("Arial",12,QFont::Bold,true));
    m_3emeAttrLab->move(440,200);
    m_3emeAttrCombo = new QComboBox (this);
    m_3emeAttrCombo->setGeometry(420,225,100,30);
    m_3emeAttrCombo->addItem("NULL");
    m_3emeAttrCombo->addItem("Oui");
    m_3emeAttrCombo->addItem("Non");


    //LABEL
    m_labelVallAttr = new QLabel ("Attributs :",this);
    m_labelVallAttr->setFont(QFont("Arial",12,QFont::Bold,true));
    m_labelVallAttr->move(50,200);

    //LabelPrenom
    m_labPrenom = new QLabel("Prenom : " , this);
    m_labPrenom->setFont(QFont("Arial",12,QFont::Bold,true));
    m_labPrenom->move(500,30);

    //LinePrenom
    m_Prenom = new QLineEdit(this);
    m_Prenom->setGeometry(600,30,120,30);


    //LabelNom
    m_labNom = new QLabel("Nom : " , this);
    m_labNom->setFont(QFont("Arial",12,QFont::Bold,true));
    m_labNom->move(522,80);

    //LineNom
    m_Nom = new QLineEdit(this);
    m_Nom->setGeometry(600,80,120,30);

    //buttonPredict
    m_bouPredict= new QPushButton("Predire",this);
    m_bouPredict->setGeometry(600,225,80,40);

    //labelScore
    m_labScore = new QLabel("fze",this);


    m_bou->setGeometry(700,550,80,40);

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(320, 300);
    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_bouPredict, SIGNAL(clicked()),
            this, SLOT(prediction()));
}
void MaFenetre::setQuitter()
{
    exit(0);
}
void MaFenetre::prediction()
{
    string resultC1= m_1erAttrCombo->currentText().toStdString();
    string resultC2=m_com->currentText().toStdString();
    string resultC3=m_3emeAttrCombo->currentText().toStdString();
    vector <string> maladie;
//    std::cout << frequence("Rhume");
    QString str = QString::fromStdString(to_string(frequence("Appendicite")));
    m_labScore->setText(str);

}

double MaFenetre::frequence(string maladie){
    double compteur = 0;
    for (unsigned i=0; i<9;++i) {
        if(m_mat[i][3] == maladie)++compteur;
    }
    return compteur/9;
}

void MaFenetre::conf(){

}



