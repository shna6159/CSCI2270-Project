#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <string>
#include <math.h>
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

    left = huffQ.front();
    huffQ.pop();

    //Remove lowest frequency node in queue
    right = huffQ.front();
    huffQ.pop();

    /*combine 2 lowest nodes into one parent node
    with lowest nodes as its children*/
    parent->frequency = left->frequency + right->frequency;
    parent->leftChild = right;
    parent->rightChild = left;
    //add combined node back to queue
    huffQ.push(parent);
  }

  root = huffQ.front();
}

std::vector<bool> addBit(std::vector<bool> code, bool bit)
{
  code.push_back(bit);
  return code;
}

void FileReading::createTable(Node* root, std::vector<bool> code, std::ofstream &compressedFile)
{
  //Instead of writing an int (0, or 1), write bits to file
  //source: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
  if(root == 0)
  {
    return;
  }
  if(root ->symbol != '\0')
  {
    compressedFile<< root->symbol;
    for(int i = 0; i < code.size(); i++)
    {
      compressedFile<< code[i];
    }
    compressedFile<< std::endl;
  }

  createTable(root->leftChild, addBit(code, true), compressedFile);
  createTable(root->rightChild, addBit(code, false), compressedFile);
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

void FileReading::putCodesInArray()
{
  std::ifstream codesFile;
  codesFile.open("codes.bin");
  std::string codesLine;

  //Read codes into prefixChar array;
  if(codesFile.is_open())
  {
    while(std::getline(codesFile, codesLine))
    {
      char symbol = codesLine[0];
      std::string code = codesLine.substr(1, codesLine.length() - 1);
      prefixChar[symbol] = code;
    }
  }
}

void FileReading::compress(std::string fileName, std::string compress)
{
  std::ifstream file;
  std::ofstream compressedFile;
  compressedFile.open(compress, std::ofstream::binary);
  file.open(fileName);
  std::string line;
  std::vector<char> allBits;
  int filledTo = 0;
  unsigned char byte = 0;

  putCodesInArray();

  //compress file
  if(file.is_open())
  {
    while(getline(file, line))
    {
      std::cout<< "Line: \'" << line << "\'" << std::endl;
      //put all codes into an array
      for(int i = 0; i < line.length(); i++)
      {
        std::cout<< "Code: " << prefixChar[line[i]] << std::endl;

        std::string code = prefixChar[line[i]];
        for(int j = 0; j < code.length(); j++)
        {
          std::cout<< "filledTo: " << filledTo << std::endl;
        //  allBits[filledTo] = code[j];
          filledTo++;
        }
      }
    }
    //split array into groups of 8
    //Source: https://stackoverflow.com/questions/29123959/convert-a-char-array-of-0-and-1-to-bytes-in-c
    int count = 0;
    uint16_t comp[(filledTo + 8 - 1) / 8];

    for(int j = 0; j < filledTo; j += 8)
    {
      for(int i = j; i < (j + 8); ++i)
      {
        if(allBits[i] == '1') byte |= 1 << (7 - i);
      }
      compressedFile<<byte;
      comp[count] = byte;
      count++;
    }

    //Place bytes into new array. Size of array is rounded up

  }
  compressedFile.close();
}

void FileReading::decompress(std::string decompress, std::string compressed)
{
  std::ofstream decompressedFile;
  decompressedFile.open(decompress);
  std::ifstream compressedFile;
  compressedFile.open(compressed, std::ifstream::binary);
  std::string code;

  if(compressedFile.is_open())
  {
    while(std::getline(compressedFile, code, ' ') || std::getline(compressedFile, code))
    {
      for(int i = 0; i < 256; i++)
      {
        if(code == prefixChar[i])
        {
          decompressedFile<< char(i);
        }
      }
    }
  }

  decompressedFile.close();
}

void FileReading::readAndCompress(std::string inputFile, std::string compressedFile, std::string decompressedFile)
{
  std::vector<bool> code;
  std::ofstream compressed;
  compressed.open("codes.bin");
  readFile(inputFile);
  createTable(root, code, compressed);
  compress(inputFile, compressedFile);
  decompress(decompressedFile, compressedFile);
}
