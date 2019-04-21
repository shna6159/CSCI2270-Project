#include "mainwindow.h"
#include <QApplication>
#include<iostream>
#include<fstream>
#include "main.cpp"
using namespace std;

void val(string a)
{
    ofstream opstream("Test.txt");


        if (opstream.is_open())
        {

            opstream << a;
        }
        else
        {

            std::cout << "Something went wrong with opening the file!";
        }


        opstream.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
