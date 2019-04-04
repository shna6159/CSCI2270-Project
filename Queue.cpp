//#include "PriorityQueue.hpp"
#include "Queue.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Queue::Queue(int _numNodes)
{
  queueFront = -1;
  queueEnd = -1;
  numNodes = _numNodes;
}

int Queue::queueSize()
{
  if(queueFront == -1)
  {
    return 0;
  }
  if(queueFront <= queueEnd)
  {
    return (queueEnd - queueFront + 1);
  }
  else
  {
    return SIZE - (queueFront - queueEnd) + 1;
  }

}


bool Queue::isEmpty()
{
  if(queueFront == -1 && queueEnd == -1)
  {
    return true;
  }
  return false;
}

bool Queue::isFull()
{
  if(queueSize() == SIZE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Queue::push(float _frequency, char _symbol, Node* _leftChild, Node* _rightChild)
{
  if(!isFull())
  {
    numNodes++;
    if(queueFront == -1)
    {
      queueFront = 0;
      queueEnd = 0;
      queue[queueEnd].frequency = _frequency;
      queue[queueEnd].symbol = _symbol;
      queue[queueEnd].leftChild = _leftChild;
      queue[queueEnd].rightChild = _rightChild;
    }
    else
    {
      if(queueEnd == SIZE - 1)
      {
        queue[queueEnd].frequency = _frequency;
        queue[queueEnd].symbol = _symbol;
        queue[queueEnd].leftChild = _leftChild;
        queue[queueEnd].rightChild = _rightChild;
        queueEnd = 0;
      }
      else
      {
        queueEnd++;
        queue[queueEnd].frequency = _frequency;
        queue[queueEnd].symbol = _symbol;
        queue[queueEnd].leftChild = _leftChild;
        queue[queueEnd].rightChild = _rightChild;
      }
    }
  }
  else
  {
    std::cout<< "Queue full, cannot push new item" << std::endl;
  }
}

Node Queue::pop()
{
  numNodes--;

  if(!isEmpty())
  {
    if(queueFront == queueEnd)
    {
      queue[queueFront].frequency = 0.0;
      queue[queueFront].symbol = '\0';
      queueFront = -1;
      queueEnd = -1;
    }
    else
    {
      if(queueFront == SIZE - 1)
      {
        queue[queueFront].frequency = 0.0;
        queue[queueFront].symbol = '\0';
        queueFront = 0;
      }
      else
      {
        queue[queueFront].frequency = 0.0;
        queue[queueFront].symbol = '\0';
        queueFront++;
      }
    }
  }
  else
  {
    std::cout<< "Queue empty, cannot pop an item" << std::endl;
  }
}

Node Queue::peek()
{
  if(isEmpty())
  {
    std::cout<< "Queue empty, cannot peek" << std::endl;
  }
  else
  {
    return queue[queueFront];
  }
}

void Queue::createHuffmanTree(Node* priorityQueueArr)
{
<<<<<<< HEAD
  Node* left = new Node();
  Node* right = new Node();
  Node* parent = new Node();
  int tempNumNodes = numNodes;
  int count = tempNumNodes;
  //make priorityQueue array a Queue array
  for(int i = 0; i < tempNumNodes; i++)
  {
    std::cout<< "numNodes: " << numNodes << std::endl;
    push(priorityQueueArr[i].frequency, priorityQueueArr[i].symbol, 0, 0);
    std::cout<< queue[i].symbol << ": " << queue[i].frequency << std::endl;
  }

  //Remove lowest frequency node in queue
  while(count > 1)
  {
    left->frequency = peek().frequency;
    std::cout<< "leftChild frequency: " << peek().frequency << std::endl;
    left->symbol = peek().symbol;
    pop();

    //Remove lowest frequency node in queue
    right->frequency = peek().frequency;
    std::cout<< "rightChild frequency: " << peek().frequency << std::endl;
    right->symbol = peek().symbol;
    pop();

    /*combine 2 lowest nodes into one parent node
    with lowest nodes as its children*/
    parent->frequency = left->frequency + right->frequency;
    parent->leftChild = left;
    parent->rightChild = right;
    std::cout<< "Parent Frequency: " << parent->frequency << std::endl << std::endl;
    //add combined node back to queue
    push('\0', parent->frequency, parent->leftChild, parent->rightChild);

    count--;
  }
=======

>>>>>>> 3ba27039364d30a2cbab23d88aa55cd7ad8038e4
}
