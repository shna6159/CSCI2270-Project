#include <iostream>
#include <queue>
#include <vector>
#include "FileReading.hpp"

Node* FileReading::getRoot()
{
  return root;
}

FileReading::FileReading()
{
  root = 0;
}

void FileReading::readFile(std::string fileName)
{

}

Node* FileReading::createHuffmanTree()
{
  while(huffQ.size() > 1)
  {
    Node* left = new Node();
    Node* right = new Node();
    Node* parent = new Node();

    left->frequency = huffQ.front()->frequency;
    std::cout<< "leftChild frequency: " << huffQ.front()->frequency <<  ", '" << huffQ.front()->symbol << "'" << std::endl;
    left->symbol = huffQ.front()->symbol;
    huffQ.pop();
    if(huffQ.empty()) break;

    //Remove lowest frequency node in queue
    right->frequency = huffQ.front()->frequency;
    std::cout<< "rightChild frequency: " << huffQ.front()->frequency << ", '" << huffQ.front()->symbol << "'" << std::endl;
    right->symbol = huffQ.front()->symbol;
    huffQ.pop();

    /*combine 2 lowest nodes into one parent node
    with lowest nodes as its children*/
    parent->frequency = left->frequency + right->frequency;
    parent->leftChild = left;
    parent->rightChild = right;
    std::cout<< "Parent Frequency: " << parent->frequency <<  ", '" << parent->symbol << "'" << std::endl << std::endl;
    //add combined node back to queue
    huffQ.push(parent);

    std::cout<< "_____________________________________" << std::endl << std::endl;
  }

  root = huffQ.front();
}

void FileReading::createTable()
{

}

void FileReading::postOrder(Node* T)
{
  if (T == 0)
  {
    return;
  }
  else
  {
    postOrder(T->leftChild);
    postOrder(T->rightChild);
    std::cout << T->frequency << " " ;
  }
  return;
}
