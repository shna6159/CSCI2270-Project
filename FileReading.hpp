#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include<algorithm>

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
    void postOrder(Node* T);
    void readFile(std::string fileName);
    void createTable(Node* root, int top);
    Node* getRoot();
  private:
    Node* createHuffmanTree();
    Node* searchQueue(char symbol);

//Variables
  private:
    std::vector <Node*> pq;
    std::queue<Node*> huffQ;
    std::set<Node*> huffmanTree;
    std::vector <char> symbolArr;
    std::vector <float> frequencyArr;
    Node* root;

};
