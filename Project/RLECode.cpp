#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std; 
  
void printRLE(string S,char* outFile);
  


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
