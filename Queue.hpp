#include "Node.hpp"


class Queue
{
  private:
    int queueFront;             // the index in queue[] that will be dequeued next
    int queueEnd;               // the index in queue[] that was most recently enqueued
    Node queue[60];
  public:
    Queue();
    void push(float _frequency, char _symbol);
    Node pop();
    void createHuffmanTree(Node* priorityQueueArr);
};
