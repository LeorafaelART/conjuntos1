#include "telaprincipal.h"
#include "ui_telaprincipal.h"
#include <QTabWidget>

//boolenao para verificar quando os 2 conjuntos forem criados
//fazendo com que os botoes com os metodos unicao etc sejam ativos
bool verA=false,verB=false;

TelaPrincipal::TelaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaPrincipal),
      CA(0),
      CB(0)
{
    ui->setupUi(this);
    ui->lineEditIncluirCA->setEnabled(false);
    ui->lineEditIncluirCB->setEnabled(false);
    ui->pushButtonIncluirCA->setEnabled(false);
    ui->pushButtonIncluirCB->setEnabled(false);
    ui->lineEditResultado->setEnabled(false);
    ui->pushButtonUniao->setEnabled(false);
    ui->pushButtonIntersecao->setEnabled(false);
    ui->pushButtonCADiferencaCB->setEnabled(false);
    ui->pushButtonCBDiferencaCA->setEnabled(false);

}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
    if(CA) delete CA;
    if(CB) delete CB;
}


void TelaPrincipal::on_pushButtonCriarCA_clicked()
{
    try {
        int tamanho = ui->lineEditTamanhoCA->text().toInt();
        CA = new ejm::Conjunto(tamanho);
        ui->lineEditIncluirCA->setEnabled(true);
        ui->pushButtonIncluirCA->setEnabled(true);
        verA=true;
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA",erro);
    } catch(std::bad_alloc &erro){
        QMessageBox::information(this,"ERRO DO SISTEMA","Conjunto não foi criado");
    }
}
void TelaPrincipal::on_pushButtonCriarCB_clicked()
{
    try {
        int tamanho = ui->lineEditTamanhoCB->text().toInt();
        CB = new ejm::Conjunto(tamanho);
        ui->lineEditIncluirCB->setEnabled(true);
        ui->pushButtonIncluirCB->setEnabled(true);
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA",erro);
    } catch(std::bad_alloc &erro){
        QMessageBox::information(this,"ERRO DO SISTEMA","Conjunto não foi criado");
    }
}


void TelaPrincipal::on_pushButtonUniao_clicked()
{
    try {
        ejm::Conjunto *uniao=CA->uniao(CB);
        ui->lineEditResultado->setText(uniao->getConjunto());
        ui->lineEditResultado->setEnabled(true);
        delete uniao;
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO", erro);
    }

}

void TelaPrincipal::on_pushButtonIntersecao_clicked()
{
    try {
        ejm::Conjunto *inter=CA->inter(CB);
        ui->lineEditResultado->setText(inter->getConjunto());
        ui->lineEditResultado->setEnabled(true);
        delete inter;
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO", erro);
    }
}


void TelaPrincipal::on_pushButtonCADiferencaCB_clicked()
{
    try {
        ejm::Conjunto *diferenca=CB->diferenca(CA);
        ui->lineEditResultado->setText(diferenca->getConjunto());
        ui->lineEditResultado->setEnabled(true);
        delete diferenca;
    } catch (QString &erro) {

        ui->lineEditResultado->setText(erro);
    }
}


void TelaPrincipal::on_pushButtonCBDiferencaCA_clicked()
{
    try {
        ejm::Conjunto *diferenca=CA->diferenca(CB);
        ui->lineEditResultado->setText(diferenca->getConjunto());
        ui->lineEditResultado->setEnabled(true);
        delete diferenca;
    } catch (QString &erro) {

        ui->lineEditResultado->setText(erro);
    }
}


void TelaPrincipal::on_pushButtonIncluirCA_clicked()
{
    try {
        verA=true;
        int elemento = ui->lineEditIncluirCA->text().toInt();
        CA->incluirElemento(elemento);
        ui->lineEditSaidaCA->setText(CA->getConjunto());
        ui->lineEditIncluirCA->clear();
        if(verA==true && verB==true)
        {
            ui->pushButtonUniao->setEnabled(true);
            ui->pushButtonIntersecao->setEnabled(true);
            ui->pushButtonCADiferencaCB->setEnabled(true);
            ui->pushButtonCBDiferencaCA->setEnabled(true);
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA",erro);
    } catch(std::bad_alloc &erro){
        QMessageBox::information(this,"ERRO DO SISTEMA","Conjunto não foi criado");
    }
}

void TelaPrincipal::on_pushButtonIncluirCB_clicked()
{
    try {
        verB=true;
        int elemento = ui->lineEditIncluirCB->text().toInt();
        CB->incluirElemento(elemento);
        ui->lineEditSaidaCB->setText(CB->getConjunto());
        ui->lineEditIncluirCB->clear();
        if(verA==true && verB==true)
        {
            ui->pushButtonUniao->setEnabled(true);
            ui->pushButtonIntersecao->setEnabled(true);
            ui->pushButtonCADiferencaCB->setEnabled(true);
            ui->pushButtonCBDiferencaCA->setEnabled(true);
        }
    } catch (QString &erro) {
        QMessageBox::information(this,"ERRO DO SISTEMA",erro);
    } catch(std::bad_alloc &erro){
        QMessageBox::information(this,"ERRO DO SISTEMA","Conjunto não foi criado");
    }
}



void TelaPrincipal::on_pushButton_clicked()
{
    QString str1 ="SIM";
    QString str2 ="NAO";

    if(CA->eVazio()==true){
     QTableWidgetItem *item1 =new QTableWidgetItem(str1);
     this->ui->tableWidgetSaida->setItem(0,0,item1);
   }
    else{
        QTableWidgetItem *item2 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(0,0,item2);
    }
    if(CB->eVazio()==true){
     QTableWidgetItem *item3 =new QTableWidgetItem(str1);
     this->ui->tableWidgetSaida->setItem(0,1,item3);
   }
    else{
        QTableWidgetItem *item4 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(0,1,item4);
    }
    //IDENDITCO REVER TA DANDO MERDA------------------------//
    if(CA->eIndentico(CB)==true){
        QTableWidgetItem *item5 =new QTableWidgetItem(str1);
        this->ui->tableWidgetSaida->setItem(1,0,item5);
    }
    else{
        QTableWidgetItem *item6 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(1,0,item6);
    }
    if(CB->eIndentico(CA)==true){
        QTableWidgetItem *item7 =new QTableWidgetItem(str1);
        this->ui->tableWidgetSaida->setItem(1,1,item7);
    }
    else{
        QTableWidgetItem *item8 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(1,1,item8);
    }
    //------------------------------------------------------//

    if(CA->subconjunto(CB)==true){
        QTableWidgetItem *item11 =new QTableWidgetItem(str1);
        this->ui->tableWidgetSaida->setItem(2,0,item11);

    }
    else{
        QTableWidgetItem *item12 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(2,0,item12);
    }

    if(CB->subconjunto(CA)==true){
        QTableWidgetItem *item13 =new QTableWidgetItem(str1);
        this->ui->tableWidgetSaida->setItem(2,1,item13);

    }
    else{
        QTableWidgetItem *item14 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(2,1,item14);
    }


    if(CA->disjunto(CB)==true){
        QTableWidgetItem *item15 =new QTableWidgetItem(str1);
        this->ui->tableWidgetSaida->setItem(3,0,item15);
    }
    else{
        QTableWidgetItem *item16 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(3,0,item16);
    }

    if(CB->disjunto(CA)==true){
        QTableWidgetItem *item17 =new QTableWidgetItem(str1);
        this->ui->tableWidgetSaida->setItem(3,1,item17);
    }
    else{
        QTableWidgetItem *item18 =new QTableWidgetItem(str2);
        this->ui->tableWidgetSaida->setItem(3,1,item18);
    }


    QString mediaA= QString::number(CA->media());
    QString mediaB= QString::number(CB->media());

    QTableWidgetItem *item9 =new QTableWidgetItem(mediaA);
    this->ui->tableWidgetSaida->setItem(4,0,item9);
    QTableWidgetItem *item10 =new QTableWidgetItem(mediaB);
    this->ui->tableWidgetSaida->setItem(4,1,item10);


    QString ampliA= QString::number(CA->amplitude());
    QString ampliB= QString::number(CB->amplitude());

    QTableWidgetItem *item19 =new QTableWidgetItem(ampliA);
    this->ui->tableWidgetSaida->setItem(5,0,item19);
    QTableWidgetItem *item20 =new QTableWidgetItem(ampliB);
    this->ui->tableWidgetSaida->setItem(5,1,item20);

}

