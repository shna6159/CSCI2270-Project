#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    QString abc = ui->lineEdit->text();

    string current_locale_text = abc.toLocal8Bit().constData();

    main
}
