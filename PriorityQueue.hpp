struct Node
{
  char symbol = ' ';
  float frequency = 0;
  Node* parent = 0;
  Node* leftChild = 0;
  Node* rightChild = 0;
};

class PriorityQueue
{

public:

  PriorityQueue(int size, int huffmanSize);

  ~PriorityQueue();

  //Adds characters and frequencies to min heap
  void enqueue(char _symbol, float _frequency);

  void dequeue();

  Node peek();

  bool isEmpty();

  bool isFull();

  void print();

  /*Takes nodes with 2 lowest freqiencies, and makes them the
  children of node of sum of their frequencies. Root node is
  the sum of all frequencies*/
  void createHuffmanTree();

  void printHuffman();

private:

  void repairUpward(int nodeIndex);
  void repairDownward(int nodeIndex);

  Node* priorityQueue;
  int currentQueueSize;
  int maxQueueSize;
};
