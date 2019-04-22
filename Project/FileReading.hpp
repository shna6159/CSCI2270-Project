#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include<algorithm>
#include <fstream>
#include <string>

struct Node
{
  char symbol = '\0';
  float frequency = 0;
  Node* parent = 0;
  Node* leftChild = 0;
  Node* rightChild = 0;

//Source: https://cboard.cprogramming.com/cplusplus-programming/89738-make_heap-comparison.html
  bool operator()(Node* &a, Node* &b)
  {
    return a->frequency > b->frequency;
  }
};


class FileReading
{
//Functions
  public:
    FileReading();
    void readAndCompress(std::string inputFile, std::string compressedFile, std::string decompressedFile);

  private:
    Node* createHuffmanTree();
    Node* searchQueue(char symbol);
    void putCodesInArray();
    void postOrder(Node* T);
    void readFile(std::string fileName);
    void createTable(Node* root, std::vector<bool> code, std::ofstream &compressedFile);
    Node* getRoot();
    void compress(std::string fileName, std::string compress);
    void decompress(std::string decompress, std::string compressed);

//Variables
  private:
    std::vector <Node*> pq;
    std::queue<Node*> huffQ;
    std::set<Node*> huffmanTree;
    std::vector <char> symbolArr;
    std::vector <float> frequencyArr;
    std::string prefixChar[256];
    Node* root;

};
