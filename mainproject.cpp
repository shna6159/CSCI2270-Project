#include "PriorityQueue.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
  //______Tests for PriorityQueue______
  PriorityQueue pq(10, 10);

  //____isFull Test____
  std::cout<< "---- isFull Test ----" << std::endl << std::endl;
  std::cout<< pq.isFull() << std::endl; //Expected Vaue: 0

  //____isEmpty Test____
  std::cout<< "---- isEmpty Test ----" << std::endl << std::endl;
  std::cout<< pq.isEmpty() << std::endl; //Expected Vaue: 1

  //____enqueue/repairUpward Test____
  std::cout<< "---- enqueue/repairUpward Test ----" << std::endl << std::endl;
  char cArr[5] = {'E', 'A', 'D', 'B', 'C'};
  int iArr[5] = {2,3,4,5,6};
  for(int i = 0; i < 5; i++)
  {
    pq.enqueue(cArr[i], iArr[i]);
  }
  pq.print();

  //____peek Test____
  std::cout<< "---- peek Test ----" << std::endl << std::endl;
  std::cout<< pq.peek().symbol << " : " << pq.peek().frequency << std::endl;

  std::cout<< "---- createHuffmanTree Test ----" << std::endl << std::endl;
  pq.createHuffmanTree(20);
  pq.print();

  //____dequeue/repairDownward Test____
  std::cout<< "---- dequeue/repairDownward Test ----" << std::endl << std::endl;
  for(int i = 0; i < 5; i++)
  {
    std::cout<< pq.peek().symbol << " : " << pq.peek().frequency << std::endl;
    pq.dequeue();
  }

  return 0;
}
