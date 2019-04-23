#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include "FileReading.hpp"
using namespace std;
#define COUNT 10

int main()
{
  FileReading fr;
  fr.readAndCompress("TestFile.txt","compressedFile.bin", "decompressedFile.txt");

//Source: StackOverflow.com
//NOTE: I could not find the specific post I used to figure this out
  streampos begin,end;
  ifstream myfile ("compressedFile.bin", ios::binary);
  begin = myfile.tellg();
  myfile.seekg (0, ios::end);
  end = myfile.tellg();
  myfile.close();
  std::cout << "Compressed size is: " << (end-begin) << " bytes.\n";

  streampos b,e;
  ifstream dec ("TestFile.txt", ios::binary);
  b = dec.tellg();
  dec.seekg (0, ios::end);
  e = dec.tellg();
  dec.close();
  std::cout << "Original size is: " << (e-b) << " bytes.\n";

  return 0;
}
