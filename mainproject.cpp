#include <iostream>
#include <queue>
#include <vector>
#include "FileReading.hpp"

int main()
{
  char cArr[5] = {'E', 'A', 'D', 'B', 'C'};
  float iArr[5] = {2,3,4,5,6};
  FileReading fr;
  fr.readFile("TestFile.txt");

  fr.postOrder(fr.getRoot());

  return 0;
}
