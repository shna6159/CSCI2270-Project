#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include "FileReading.hpp"
#define COUNT 10

void print2DUtilHelper(Node *currNode, int space)
{
    // Base case
    if (currNode == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtilHelper(currNode->rightChild, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("\'%c\'\n", currNode->symbol);

    // Process left child
    print2DUtilHelper(currNode->leftChild, space);
}

void print2DUtil(int space, Node* root)
{
  print2DUtilHelper(root, space);
}


int main()
{
  char cArr[5] = {'E', 'A', 'D', 'B', 'C'};
  float iArr[5] = {2,3,4,5,6};
  FileReading fr;
  fr.readFile("TestFile.txt");
  std::cout<< "Post Order" << std::endl << std::endl;
  fr.postOrder(fr.getRoot());
  std::cout<< "Print Tree" << std::endl << std::endl;
  print2DUtil(3, fr.getRoot());
  std::cout<< "Print Codes" << std::endl << std::endl;
  std::vector<bool> code;
  std::ofstream compressedFile;
  compressedFile.open("codes.txt", std::ofstream::binary);
  fr.createTable(fr.getRoot(), code, compressedFile);
  fr.compress("TestFile.txt", "compressedFile.txt");
  fr.decompress("decompressedFile.txt", "compressedFile.txt");

  return 0;
}
