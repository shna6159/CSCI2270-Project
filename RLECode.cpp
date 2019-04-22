#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std; 
  
void RLE(string S,char* outFile);
  

int main(int argc, char *argv[]) 
{ 
    ifstream fileI;
    string Str;
    fileI.open(argv[1]);
    char* outFile = argv[2];
    while (getline(fileI,Str)){ // take each line in and pass it to the print function
        RLE(Str,outFile); // printout value
    }  
    fileI.close();
    return 0; 
} 

void RLE(string S,char* outFile) 
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
