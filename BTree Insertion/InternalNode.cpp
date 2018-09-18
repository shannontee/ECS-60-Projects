#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()

void InternalNode::changeMinimum(BTreeNode* ptr)
{
  int i;
  for(i = 0; i < count; i++)
  {
    if(children[i] == ptr)
      break;
  }
  keys[i] = ptr->getMinimum();

  if(parent && i == 0)
    parent->changeMinimum(this);
}

int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

void InternalNode::insert(BTreeNode *newNode) // insert from a sibling
{
	 
  int i, x;

  if((newNode->getMinimum() > keys[count-1]) && (count < internalSize))
  {
    keys[count] = newNode->getMinimum();
    children[count] = newNode;
    count++;
    newNode->setParent(this);
  
    if(parent)
      parent->changeMinimum(this);
  } // value greater than all current internal node

  else
  {
    for(i = (count-1); i>0 && keys[i] > newNode->getMinimum(); i--);
  
    for(x = (count-1); x >= (i); x--) 
    {
      keys[x+1] = keys[x];
      children[x+1] = children[x];
    }
 
    keys[i] = newNode->getMinimum();
    children[i] = newNode;
    count++;
    newNode->setParent(this);

    if(parent)
      parent->changeMinimum(this);
  }
} // InternalNode::insert()

InternalNode* InternalNode::insert(int value)
{
  int i, x;
  BTreeNode* ptr;
  
  for(i = (count-1); i>0 && keys[i] > value; i--);
  
  ptr = children[i]->insert(value);
  if(!ptr)
  {
    if(parent)
      parent->changeMinimum(this);
    return NULL;
  }

  else if(count < internalSize)
  {
    for(x = (count-1); x >= (i+1); x--)
    {
      keys[x+1] = keys[x];
      children[x+1] = children[x];
    }

    keys[i+1] = ptr->getMinimum();
    children[i+1] = ptr;
    count++;
    ptr->setParent(this);
    if(parent)
      parent->changeMinimum(this);
    return NULL;
  }

  else if(leftSibling && leftSibling->getCount() < internalSize)
  {
    if(ptr->getMinimum() < keys[0])
      ((InternalNode*)leftSibling)->insert(ptr);
     
    else
    {  
       ((InternalNode*)leftSibling)->insert(children[0]);
       
       for(i = 0; i < (count-1); i++)
       {
         children[i] = children[i+1];
         keys[i] = keys[i+1];
       }

       count--;
       this->insert(ptr);
       parent->changeMinimum(this);
    }

    if(parent)
      parent->changeMinimum(this);
    return NULL;
  }

  else if(rightSibling && rightSibling->getCount() < internalSize)
  {
    if(ptr->getMinimum() < keys[count-1]) // move greatest value to rightSibling
    {
      ((InternalNode*)rightSibling)->insert(children[count-1]);
      int j;
      for(j = count-2; keys[j] > ptr->getMinimum() && j >= 0; j--)
      {	            
        keys[j+1] = keys[j];
        children[j+1] = children[j];
      }
      keys[j+1] = ptr->getMinimum();
      children[j+1] = ptr; 
      count++ ;
    }

    else  // value should be inserted into Right Sibling
      ((InternalNode*)rightSibling)->insert(ptr);
 
    if(parent)
      parent->changeMinimum(this);
    count--;
    return NULL;
   }

   else 
   {
     int i;
     InternalNode* rightSib = new InternalNode(internalSize, leafSize, parent, this, rightSibling);

     if(rightSibling)
       rightSibling->setLeftSibling(rightSib);

     rightSibling = rightSib;

     if(ptr->getMinimum() > keys[count-1])
     {
       for(i = (internalSize+1)/2; i < internalSize; i++)
       {
	 rightSib->children[rightSib->count] = children[i];
	 rightSib->keys[rightSib->count] = keys[i];
         rightSib->count++;
	 children[i]->setParent(rightSib);
       }

       count = (internalSize+1)/2;
       rightSib->keys[rightSib->count] = ptr->getMinimum();
       rightSib->children[rightSib->count] = ptr;
       rightSib->count++;
     }

     else
     {
	int j;
        int temp = keys[count-1];
	BTreeNode* tempPtr = children[count-1];

        for(j = internalSize-2; keys[j] > ptr->getMinimum() && j >= 0; j--)
	{
	  keys[j+1] = keys[j];
          children[j+1] = children[j];
	}	
	  keys[j+1] = ptr->getMinimum();
	  children[j+1] = ptr;

        for(i = (internalSize+1)/2; i < internalSize; i++)
	{
	  rightSib->children[rightSib->count] = children[i];
	  rightSib->keys[rightSib->count] = keys[i];
	  rightSib->count++;
								                                 
 	  children[i]->setParent(rightSib);
												                 
        }

        count = (internalSize+1)/2;

	rightSib->keys[rightSib->count] = temp;
	rightSib->children[rightSib->count] = tempPtr;
	rightSib->count++;
    }
    return rightSib; 
    
  }

  return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1

  count = 2;
  keys[0] = oldRoot->getMinimum(); 
  keys[1] = node2->getMinimum();  

  children[0] = oldRoot;
  children[1] = node2; 

  oldRoot->setParent(this);
  oldRoot->setRightSibling(node2);
  node2->setParent(this);
  node2->setLeftSibling(oldRoot);

} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


