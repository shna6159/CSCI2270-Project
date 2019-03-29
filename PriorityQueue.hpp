struct Node
{
  char symbol;
  float frequency;
};

class PriorityQueue
{
  PriorityQueue(int size);

  ~PriorityQueue();

  //All letters should be leaf nodes. leftChild is
  void enqueue(char _symbol, float _frequency);

  void dequeue();
  
  Node peek();

private:

  void repairUpward(int nodeIndex);
  void repairDownward(int nodeIndex);

  Node* priorityQueue;
  int currentQueueSize;
  int maxQueueSize;
};
