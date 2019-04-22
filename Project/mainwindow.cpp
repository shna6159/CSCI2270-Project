#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileReading.hpp"
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

void printRLE(string S,char* outFile)
{
    ofstream fileo;
    fileo.open(outFile, ofstream::out | ofstream::app);  // open latest saved version of the file
    int n = S.length();
    for (int i = 0; i < n; i++) {
        int counter = 1; //counter
        while (i < n - 1 && S[i] == S[i + 1]) { //compare string values
            i++;
            counter++;
        }
        fileo << counter << S[i]<<" "; // writing code to another file
        cout << counter << S[i]<<" "; // printing out code
    }
    fileo.close();
}


void MainWindow::on_pushButton_3_clicked()
{
    close();
}

void MainWindow::on_RLEButton_clicked()
{
    QString name = ui->lineEditname->text();
    string Name = name.toLocal8Bit().constData();
    QString comp = ui->lineEditcomp->text();

    QByteArray ba = comp.toLocal8Bit();
      char *Comp = ba.data();

    ifstream fileI;
    string Str;
    fileI.open(Name);
    char* outFile = Comp;
    while (getline(fileI,Str)){ // take each line in and pass it to the print function
        printRLE(Str,outFile); // printout value
    }
    fileI.close();
}

void MainWindow::on_HuffmanButton_clicked()
{
    QString name = ui->lineEditname->text();
    string Name = name.toLocal8Bit().constData();
    QString comp = ui->lineEditcomp->text();
    string Comp = comp.toLocal8Bit().constData();
    QString decomp = ui->lineEditdecomp->text();
    string Decomp = decomp.toLocal8Bit().constData();

    Name = Name + ".txt";
    Comp = Comp +".bin";
    Decomp = Decomp + ".txt";
    FileReading fr;
   fr.readAndCompress(Name,Comp, Decomp);
    //fr.readAndCompress("HarryPotter.txt","compressedFile.bin", "decompressedFile.txt");

}
