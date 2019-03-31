#include "PriorityQueue.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int parent(int index) {return (index-1)/2;}
int leftChild(int index) {return 2*index+1;}
int rightChild(int index) {return 2*index+2;}
void swap(Node &x, Node &y) {Node z = x; x = y; y = z;}

PriorityQueue::PriorityQueue(int size, int huffmanSize)
{
  maxQueueSize = size;
  currentQueueSize = 0;
  priorityQueue = new Node[size];
}

PriorityQueue::~PriorityQueue()
{
  delete [] priorityQueue;
}

bool PriorityQueue::isEmpty()
{
  if(currentQueueSize == 0)
    return true;
  else
    return false;
}

bool PriorityQueue::isFull()
{
  if(currentQueueSize >= maxQueueSize)
  {
    return true;
  }
  return false;
}

Node PriorityQueue::peek()
{
  if(isEmpty())
  {
    std::cout<< "Heap empty, nothing to peek" << std::endl;
  }
  return priorityQueue[0];
}


void PriorityQueue::repairUpward(int nodeIndex)
{
  if(priorityQueue[nodeIndex].frequency < priorityQueue[parent(nodeIndex)].frequency)
  {
    swap(priorityQueue[parent(nodeIndex)], priorityQueue[nodeIndex]);
    repairUpward(parent(nodeIndex));
  }
  else
  {
    return;
  }
}

void PriorityQueue::enqueue(char _symbol, float _frequency)
{
  Node add;
  add.symbol = _symbol;
  add.frequency = _frequency;

  if(isFull())
  {
    std::cout<< "Heap full, cannot enqueue" << std::endl;
    return;
  }

  priorityQueue[currentQueueSize] = add;
  repairUpward(currentQueueSize);
  currentQueueSize++;
}

void PriorityQueue::repairDownward(int nodeIndex)
{
  int max = nodeIndex;
  int l = leftChild(nodeIndex);
  int r = rightChild(nodeIndex);

  if(l > nodeIndex && priorityQueue[l].frequency < priorityQueue[max].frequency && l < currentQueueSize)
  {
    max = l;
  }
  else if(r > nodeIndex && priorityQueue[r].frequency < priorityQueue[max].frequency && r < currentQueueSize)
  {
    max = r;
  }

  if(max != nodeIndex)
  {
    swap(priorityQueue[nodeIndex], priorityQueue[max]);
    repairDownward(nodeIndex);
  }
}

void PriorityQueue::dequeue()
{
  if(isEmpty())
  {
    std::cout<< "Heap empty, cannot dequeue" << std::endl;
    return;
  }
  else if(currentQueueSize == 1)
  {
    currentQueueSize--;
    return;
  }
  else
  {
    priorityQueue[0] = priorityQueue[currentQueueSize - 1];
    currentQueueSize--;
    repairDownward(0);
  }
}

void PriorityQueue::print()
{
  for(int i = 0; i < currentQueueSize; i++)
  {
    std::cout<< priorityQueue[i].symbol << ": " << priorityQueue[i].frequency <<std::endl;
  }
}

void PriorityQueue::createHuffmanTree()
{
  /*
  -----Sources Used-----
  https://courses.cs.washington.edu/courses/cse143/19wi/lectures/03-08/slides/huffman_lecture.pdf
  https://en.wikipedia.org/wiki/Huffman_coding
  https://www.youtube.com/watch?v=co4_ahEDCho

  */

  std::cout<< currentQueueSize << std::endl;
  while(currentQueueSize > 1)
  {
    Node* left;
    Node* right;
    Node* parent;

    //Remove lowest node in queue
    std::cout<< peek().frequency << std::endl;
    left->frequency = peek().frequency;
    left->symbol = peek().symbol;
    dequeue();

    //Remove second lowest node in queue
    //std::cout<< peek().frequency << std::endl;
    right->frequency = peek().frequency;
    right->symbol = peek().symbol;
    dequeue();
    //combine 2 lowest nodes into one node
    parent->frequency = left->frequency + right->frequency;
    parent->leftChild = left;
    parent->rightChild = right;

    //add combined node back to queue
    enqueue(' ', parent->frequency);
    std::cout<< currentQueueSize;
    currentQueueSize--;
  }
}
