#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;


int main(int argc, char *argv[]) 
{ 
    ifstream fileI; // stream in input file
    string Str,Value,Value2;
    fileI.open(argv[1]); //open file
    getline(fileI,Str);//get full line in file
    int n = Str.length(); // get length of the string
    fileI.close(); // close to reset cursor to begining of the file
    fileI.open(argv[1]);
    ofstream fileo;
    char* outFile = argv[2];
    fileo.open(outFile, ofstream::out | ofstream::app);
    for (int j=0; j<n/4; j++){
        getline(fileI,Value,' '); // get number value from string
        getline(fileI,Value2,' ');  //get charicter from string
        int number = stoi(Value);
        for (int i=0;i<number;i++){  // put the charicter in the output file as many times as specified 
            fileo<<Value2;
        }
    }
    fileI.close();
    fileo.close();
    return 0;
}
