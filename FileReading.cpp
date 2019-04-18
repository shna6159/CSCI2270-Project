#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include "FileReading.hpp"

Node* FileReading::getRoot()
{
  return root;
}

FileReading::FileReading()
{
  root = 0;
}

Node* FileReading::searchQueue(char symbol)
{
  for(int i = 0; i < pq.size(); i++)
  {
    if(pq[i]->symbol == symbol)
    {
      return pq[i];
    }
  }
  return 0;
}

void FileReading::readFile(std::string fileName)
{
  std::ifstream file;
  file.open(fileName);
  std::string line;
  std::multiset<char> hashTable;

//Add characters to hash table
  if(file.is_open())
  {
    while(getline(file, line))
    {
      for(int i = 0; i < line.length(); i++)
      {
        hashTable.insert(line[i]);
      }
    }
  }

  //Add elements to vector pq
  for (auto it = hashTable.begin(); it != hashTable.end(); ++it)
  {
    Node* add = new Node();
    add->symbol = *it;
    if(hashTable.find(*it) != hashTable.end())
    {
      add->frequency = hashTable.count(*it);
    }

    pq.push_back(add);
  }

  //Remove duplicate elements from pq
  for(int i = 0; i < pq.size(); i++)
  {
    for(int j = i - 1; j < pq.size(); j++)
    {
      if(pq[i]->symbol == pq[j]->symbol)
      {
        pq.erase(pq.begin() + j);
      }
    }
  }

  //Turn vector into heap
  std::make_heap(pq.begin(), pq.end(), Node());

  //put elements from vector into queue, so Huffman Tree can be made
  int originalPQSize = pq.size();

  for(int i = 0; i < originalPQSize; i++)
  {
    huffQ.push(pq.front());
    pq.erase(pq.begin());
    std::make_heap(pq.begin(), pq.end(), Node());
  }

  //Now that all nodes are in queue, make huffman tree
  createHuffmanTree();
}

Node* FileReading::createHuffmanTree()
{
  while(huffQ.size() > 1)
  {
    Node* left = new Node();
    Node* right = new Node();
    Node* parent = new Node();

    //left->frequency = huffQ.front()->frequency;
    left = huffQ.front();
    std::cout<< "leftChild frequency: " << huffQ.front()->frequency <<  ", '" << huffQ.front()->symbol << "'" << std::endl;
    huffQ.pop();

    //Remove lowest frequency node in queue
    right = huffQ.front();
    std::cout<< "rightChild frequency: " << huffQ.front()->frequency << ", '" << huffQ.front()->symbol << "'" << std::endl;
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

void FileReading::createTable(Node* root, int top)
{
  //std::vector<char, int> table;
  std::vector<int> code;

  if(root->leftChild != 0)
  {
    code.insert(code.end(), 0);
    createTable(root->leftChild, top + 1);
  }

  if(root->rightChild != 0)
  {
    code.insert(code.end(), 1);
    createTable(root->rightChild, top + 1);
  }

  if(!(root->leftChild) && !(root->rightChild))
  {
    printf("%c: ", root->symbol);
    std::cout<< "Size: " << code.size() << std::endl;
    for(int i = 0; i < code.size(); i++)
    {
      std::cout<< code[i];
    }
  }

}

void FileReading::postOrder(Node* T)
{
  if (T == 0)
  {
    return;
  }
  else
  {
    std::cout << "\'" << T->symbol << "\' " ;
    postOrder(T->leftChild);
    postOrder(T->rightChild);
  }
  return;
}
