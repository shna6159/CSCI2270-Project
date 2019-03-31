#ifndef NODE_H
#define NODE_H
struct Node
{
  char symbol = ' ';
  float frequency = 0;
  Node* parent = 0;
  Node* leftChild = 0;
  Node* rightChild = 0;
};
#endif
