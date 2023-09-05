#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <QFileDialog>

#include "eleve.h"
#include "activite.h"
#include "association.h"

#include "eleve_am.h"
#include "activiteui.h"
#include "associationui.h"

#include <QException>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialiser(int page);

private slots:
    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_supprimer_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tri_clicked();

    void on_pushButton_clicked();

    void on_mail_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_archive_clicked();

private:
    Ui::MainWindow *ui;

    int page=0;
    int archive=0;

    AssociationUI *association;

    Eleve E;
    Activite A;
    Association As;


};
#endif // MAINWINDOW_H
