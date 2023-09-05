#include "mainw.h"
#include "mainwindow.h"
#include "ui_mainw.h"

MainW::MainW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainW)
{
    ui->setupUi(this);

}

MainW::~MainW()
{
    delete ui;
}

void MainW::on_pushButton_clicked()
{

    this->showTransactionPage();

}

void MainW::on_pushButton_2_clicked()
{
    MainWindow* w = new MainWindow(this);
    w->initialiser(1);
    w->show();
}


void MainW::showTransactionPage()
{



}
