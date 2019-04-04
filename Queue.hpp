#include "Node.hpp"

const int SIZE = 60;

class Queue
{
  private:
    int queueFront;             // the index in queue[] that will be dequeued next
    int queueEnd;             // the index in queue[] that was most recently enqueued
    Node queue[SIZE];
    int numNodes;
  public:
    Queue(int _numNodes);
    bool isEmpty();
    bool isFull();
    int queueSize();
    void push(float _frequency, char _symbol, Node* _leftChild, Node* _rightChild);
    Node pop();
    Node peek();
    void createHuffmanTree(Node* priorityQueueArr);
};
