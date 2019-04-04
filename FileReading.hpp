#include <iostream>
#include <queue>
#include <vector>

struct Node
{
  char symbol = '\0';
  float frequency = 0;
  Node* parent = 0;
  Node* leftChild = 0;
  Node* rightChild = 0;

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
    Node* getRoot();
  private:
    Node* createHuffmanTree();
    void createTable();

//Variables
  private:
    std::priority_queue <Node*, std::vector<Node*>, Node> pq;
    std::queue<Node*> huffQ;
    std::vector <char> symbolArr;
    std::vector <float> frequencyArr;
    Node* root;

};
