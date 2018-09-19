#include <iostream>
#include <fstream>
#include <cstdlib>
#include "QueueAr.h"
#include "StackLi.h"

using namespace std;

int main(int argc, char** argv)
{
  short num;
  Queue<short>* queuePtr; 
  queuePtr = new Queue<short> (atoi(argv[2]));
  StackLi<Queue<short>*> containerStack;
  
  ifstream inf(argv[1]);

  while(inf>>num)
  {
    queuePtr->enqueue(num);
    if ((queuePtr->isFull()))
      {
        containerStack.push(queuePtr);
        queuePtr = new Queue<short> (atoi(argv[2]));
      }
  }

  if(!(queuePtr->isEmpty()))
    containerStack.push(queuePtr);

  while(!(containerStack.isEmpty()))
  {
    queuePtr = containerStack.topAndPop();

    while(!(queuePtr->isEmpty()))
      cout  << queuePtr->dequeue() << ' ' ;
  }

  inf.close();
  return 0;
}
