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


