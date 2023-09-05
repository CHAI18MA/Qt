#ifndef MAINW_H
#define MAINW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "mainwindow.h"

#include <QLayoutItem.h>
#include <QVBoxLayout>

namespace Ui {
class MainW;
}

class MainW : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainW(QWidget *parent = nullptr);
    ~MainW();

    void showTransactionPage();

    QStackedWidget getStackedWidget() const;
    void setStackedWidget(const QStackedWidget &value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainW *ui;


};

#endif // MAINW_H
