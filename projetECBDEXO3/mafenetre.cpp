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
    m_labScore = new QLabel("",this);
    m_labScore->setGeometry(0,0,200,50);

    //Table
    m_tab = new QTableWidget(m_mat.size(),m_mat[0].size(),this);
    m_tab->setGeometry(200,300,400,300);

    for (unsigned i=0;i<m_mat.size();++i) {
        for (unsigned j=0 ;j<m_mat[0].size();++j) {
            m_tab->setItem(i,j,new QTableWidgetItem(QString::fromStdString(m_mat[i][j])));

        }

    }

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
    CVString maladies= getMaladies();

    vector <double> Score={0.0,-1.0};
    for (double i=0;i<maladies.size();++i) {
        double freq = frequence(maladies[i]);
        vector <double> scoreTemp ={freq
                                    *conf("Fievre",maladies[i],resultC1,freq)
                                    *conf("Douleur",maladies[i],resultC2,freq)
                                    *conf("Toux",maladies[i],resultC3,freq),i};
        if(scoreTemp[0]>Score[0]){
            Score=scoreTemp;
        }else if(scoreTemp[0]==Score[0]){
            Score.push_back(scoreTemp[1]);
        }
    }
    QString str;
    if(Score.size()>2){
        str = QString::fromStdString(maladies[Score[1]] +" ou "+ maladies[Score[2]]);
    }else {
        str = QString::fromStdString(maladies[Score[1]]);
    }
    if(Score[0] == 0.0)str = QString::fromStdString("rien n'a été trouvé dans la base");
    m_labScore->setText(str);

}

double MaFenetre::frequence(string maladie){
    double compteur = 0;
    for (unsigned i=0; i<m_mat.size();++i) {
        if(m_mat[i][3] == maladie)++compteur;
    }
    return compteur/m_mat.size();
}

double MaFenetre::conf(string symptome,string maladie,string valSymptome, double freq){
    if(valSymptome=="NULL")return 1.0;
    double compteur=0;
    int col = findCol(symptome);
    for (unsigned i = 0; i<m_mat.size() ; ++i) {
        if(maladie == m_mat[i][3] && valSymptome == m_mat[i][col]){
            ++compteur;
        }
    }
    return (compteur/m_mat.size())/freq;
}

int MaFenetre::findCol(string symptome){
    for (unsigned i=0;i<m_vet.size();++i) {
        if(symptome == m_vet[i])return i;
    }
    return -1;
}

vector <string> MaFenetre::getMaladies(){
    vector <string> maladies;
    for (unsigned i=0;i<m_mat.size();++i) {
        if(!isPresent(m_mat[i][3],maladies))maladies.push_back(m_mat[i][3]);
    }
    return maladies;
}

bool MaFenetre::isPresent(string str, vector <string> VStr){
    for (unsigned i=0;i<VStr.size() ;++i) {
        if(VStr[i]==str)return true;
    }
    return false;
}



