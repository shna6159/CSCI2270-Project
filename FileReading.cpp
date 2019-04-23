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
#include <bitset>


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
    for(int j = i + 1; j < pq.size(); j++)
    {
      if(pq[i]->symbol == pq[j]->symbol)
      {
        pq.erase(pq.begin() + j);
        j--;
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

void inOrder(Node* T)
{
  if (T == 0)
  {
    return;
  }
  else
  {
    inOrder(T->leftChild);
    std::cout << "\'" << T->symbol << "\' " ;
    inOrder(T->rightChild);
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

  putCodesInArray();

  //compress file
  if(file.is_open())
  {
    while(getline(file, line))
    {
      //put all codes into an array
      for(int i = 0; i < line.length(); i++)
      {
        std::string code = prefixChar[line[i]];
        for(int j = 0; j < code.length(); j++)
        {
          allBits.push_back(code[j]);
          filledTo++;
        }
      }
    }
    //split array into groups of 8
    //Source: https://stackoverflow.com/questions/29123959/convert-a-char-array-of-0-and-1-to-bytes-in-c
    int count = 0;
    uint8_t comp[(filledTo + 8 - 1) / 8];

    for(int j = 0; j < filledTo; j += 8)
    {
      unsigned char byte = 0;
      for(int i = j; i < (j + 8); ++i)
      {
        if(allBits[i] == '1'){
          byte |= 1 << (7 - i%8);
        }
      }
      compressedFile<<byte;
      comp[count] = byte;
      count++;
    }
  }
  compressedFile.close();
}

void FileReading::decompress(std::string decompress, std::string compressed)
{
  std::ofstream decompressedFile;
  decompressedFile.open(decompress);
  std::ifstream compressedFile;
  compressedFile.open(compressed, std::ifstream::binary);
  std::string bitLine;
  Node* n = root;
  char c;
  if(compressedFile.is_open())
  {
    //Recieved help with reading/writing bits from Prashil Bhimani
    //Source: https://stackoverflow.com/questions/7349689/how-to-print-using-cout-the-way-a-number-is-stored-in-memory
    std::vector<int> bits;
    std::vector<std::bitset<8>> bytes;
    int numBytes = 0;
    while(compressedFile.read(&c, 1))
    {
      std::bitset<8> x(c);
      bytes.insert(bytes.begin(), x);
    }


    for(int i = 0; i < bytes.size(); i++)
    {
      std::bitset<8> oneByte = bytes[i];
      for(int j = 0; j < oneByte.size(); j++)
      {
        if(oneByte[j] == 1)
        {
          bits.insert(bits.begin(), 1);
        }
        if(oneByte[j] == 0)
        {
          bits.insert(bits.begin(), 0);
        }
      }
    }

    n = root;
    for(int i = 0; i < bits.size(); i++)
    {
      if(bits[i] == 1)
      {
        if(n->leftChild == NULL)
        {
            decompressedFile<< n->symbol;
            n = root;
            i--;
          }
          else
          {
            n = n->leftChild;
          }
        }
        else if(bits[i] == 0)
        {
          if(n->rightChild == NULL)
          {
              decompressedFile<< n->symbol;
              n = root;
              i--;
            }
            else
            {
              n = n->rightChild;
            }
        }
      }
    }
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
