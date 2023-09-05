#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList n = A.notifcation();

    ui->stackedWidget->setCurrentIndex(0);


    ui->label->setText(n.join('\n'));

    /*QMessageBox::information(nullptr, QObject::tr("notification des activite d'aujourd'hui"),
                 QObject::tr(n.join('\n').toUtf8().constData()), QMessageBox::Cancel);*/

    this->initialiser(this->page);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialiser(int page){

    ui->typeRecharche->clear();
    QChart *chart = new QChart();

    if(page==0){
        ui->typeRecharche->addItem("matricule");
        ui->typeRecharche->addItem("nom");
        ui->typeRecharche->addItem("prenom");
        ui->typeRecharche->addItem("email");

        ui->View->setModel(E.afficher());

        ui->pushButton_6->show();
        ui->archive->hide();

        ui->mail->setText("imprimer");

        chart->addSeries(E.statistique());


     }
    else if(page==1){

        ui->typeRecharche->addItem("matricule");
        ui->typeRecharche->addItem("titre");
        ui->typeRecharche->addItem("type");

        ui->View->setModel(A.afficher(this->archive));
        qDebug() << this->archive;

        ui->pushButton_6->hide();
        ui->archive->show();

        ui->mail->setText("archive");

        chart->addSeries(A.statistique());

    }

    chart->legend()->show();

    QChartView* chartView = new QChartView(chart,ui->stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(380,380);

    chartView->show();
}


void MainWindow::on_pushButton_2_clicked()
{

    if(this->page==0){
        eleve_am* e = new eleve_am(this);
        e->setMode(0);
        e->show();
    }
    else if(this->page==1){
        ActiviteUI* a = new ActiviteUI(this);
        a->setMode(0);
        a->show();
    }

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1==""){
        if(this->page == 0){
            ui->View->setModel(E.afficher());
        }
        else if(this->page == 1){
            ui->View->setModel(A.afficher(this->archive));
        }
    }
    else{
        QString type = ui->typeRecharche->currentText();
        if(this->page == 0){
            ui->View->setModel(E.rechercher(arg1,type));
        }
        else if(this->page == 1){
            ui->View->setModel(A.rechercher(arg1,type,this->archive));
        }
    }
}

void MainWindow::on_pushButton_3_clicked()

{
    QSqlQueryModel *model  = qobject_cast<QSqlQueryModel*>(ui->View->model());

    QWidget parent;

    QString directoryPath = QFileDialog::getExistingDirectory(&parent, "Select Directory", "");

    if(page==0){
       E.exporterCSV(directoryPath+"/eleve.csv",model);
    }
    else if(page==1){
       A.exporterCSV(directoryPath+"/activite.csv",model);
    }


}

void MainWindow::on_supprimer_clicked()
{

    QAbstractItemModel *model  = ui->View->model();

    QModelIndexList selected_indexes = ui->View->selectionModel()->selectedRows();


     if (selected_indexes.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                   QObject::tr("selectionné un element de la list"), QMessageBox::Cancel);
     }
     else{

        QModelIndex selected_index = selected_indexes.at(0);

        QString matricule = model->data(model->index(selected_index.row(),0)).toString();

        if(this->page == 0){
            E.supprimer(matricule);
        }
        else if(this->page == 1){
            A.supprimer(matricule);
        }

        this->initialiser(this->page);
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->page = 0;
    this->initialiser(this->page);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->page = 1;
    this->initialiser(this->page);
}

void MainWindow::on_tri_clicked()
{
    QString type = ui->typeRecharche->currentText();


    if(this->page == 0){
        ui->View->setModel(E.tri(type));
    }
    else if(this->page == 1){
        ui->View->setModel(A.tri(type,this->archive));
    }

}



void MainWindow::on_pushButton_clicked()
{
    QAbstractItemModel *model  = ui->View->model();

    QModelIndexList selected_indexes = ui->View->selectionModel()->selectedRows();


     if (selected_indexes.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                   QObject::tr("selectionné un element de la list"), QMessageBox::Cancel);
     }
     else{

        QModelIndex selected_index = selected_indexes.at(0);

        QString matricule = model->data(model->index(selected_index.row(),0)).toString();

        if(this->page==0){
            eleve_am* e = new eleve_am(this);
            e->setMode(1);
            e->setSelected(selected_index);
            e->setModel(model);
            e->initInput();
            e->show();
        }
        else if(this->page==1){
            ActiviteUI* a = new ActiviteUI(this);
            a->setMode(1);
            a->setSelected(selected_index);
            a->setModel(model);
            a->initInput();
            a->show();
        }

    }
}

void MainWindow::on_mail_clicked()
{
    QAbstractItemModel *model  = ui->View->model();

    QModelIndexList selected_indexes = ui->View->selectionModel()->selectedRows();


     if (selected_indexes.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                   QObject::tr("selectionné un element de la list"), QMessageBox::Cancel);
     }
     else{

        QModelIndex selected_index = selected_indexes.at(0);

        if(this->page==0){
            QString matricule = model->data(model->index(selected_index.row(),0)).toString();
            QString nom = model->data(model->index(selected_index.row(),1)).toString();
            QString prenom = model->data(model->index(selected_index.row(),2)).toString();
            E.imprimer(matricule,nom,prenom);
        }
        else if(this->page==1){
            int a;
            if (this->archive==1){
                a=0;
            }
            else if (this->archive==0){
                a=1;
            }
            QString matricule = model->data(model->index(selected_index.row(),0)).toString();
            A.archiver(matricule,a);
            this->initialiser(this->page);
        }
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    QAbstractItemModel *model  = ui->View->model();

    QModelIndexList selected_indexes = ui->View->selectionModel()->selectedRows();


     if (selected_indexes.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                   QObject::tr("selectionné un element de la list"), QMessageBox::Cancel);
     }
     else{

        QModelIndex selected_index = selected_indexes.at(0);

        QString matricule = model->data(model->index(selected_index.row(),0)).toString();


        association = new AssociationUI();
        association->setMatricule(matricule);
        association->initialiser();
        association->show();

     }

}



void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}



void MainWindow::on_archive_clicked()
{
    if(this->archive==0){
        this->archive = 1;
    }
    else{
        this->archive = 0;
    }
    qDebug() << this->archive;
    this->initialiser(1);
}
