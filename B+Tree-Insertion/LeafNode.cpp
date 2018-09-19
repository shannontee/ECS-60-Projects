#include <iostream>
#include <cstdlib>
#include <math.h>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;

int compare(const void * num1, const void * num2)
{
  return( *(int*) num1 - *(int*) num2);
}

void LeafNode::leafSort(int value)
{
  int i;
 
  if(count > 0)
  {
    for(i=(count-1); i>=0; i--)
    { 
      if(value>values[i])
        break;
      else
        values[i+1] = values[i];
    }
    values[i+1] = value;
  }
 
  else
    values[0] = value;
} 

LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int i;
  LeafNode* rightSib;
  
  if(count < leafSize)
  {
    leafSort(value);
    count++;

   if(value == values[0] && parent)
     parent->changeMinimum(this);
 
   return NULL;
  }

  else if(count == leafSize)
  {
   if(leftSibling && leftSibling->getCount() < leafSize) // passing to left sibiling
   {
     if(value < this->getMinimum()){
        leftSibling->insert(value); 
     }
     else 
     {
       leftSibling->insert(this->getMinimum());

       for(int i=1; i<count; i++)
          values[i-1] = values[i];

       parent->changeMinimum(this);
       count--;
       this->insert(value);
     }
     if(parent)
       parent->changeMinimum(this);
     return NULL;
   }
  else if (rightSibling && rightSibling->getCount() < leafSize) // passing to right sibling
  {
    if(value < rightSibling->getMinimum() && value < this->values[count-1]) // move greatest value to rightSibling
    {
      rightSibling->insert(this->values[count-1]);
      count--;
      this->insert(value);
    }
    else{  // value should be inserted into Right Sibling
      rightSibling->insert(value);
    }
    if(parent)
      parent->changeMinimum(this);
    return NULL;
  }

  else // splitting nodes
  {
 
    rightSib = new LeafNode(leafSize, parent, this, rightSibling);

    if(rightSibling)
      rightSibling->setLeftSibling(rightSib);

    rightSibling = rightSib;
     
    i = (leafSize+1)/2;
 
    if (value > values[count-1])
    {
       for (; i< leafSize; i++)
       {
	 rightSib->insert(values[i]);
       }
       count = (leafSize+1)/2;
       rightSib->insert(value);
    }  
    else 
    {
      int j;
      int temp = this->values[count-1];

      for(j = count-2; values[j] > value && j >= 0; j--)
	 values[j+1] = values[j];
      values[j+1] = value;

      for (; i< leafSize;i++)
      {
	rightSib->insert(values[i]);
      }
	count = (leafSize+1)/2;
	rightSib->insert(temp);
    }

    if(value == values[0] && parent)
	    parent->changeMinimum(this);
  }
}
  return rightSib; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


