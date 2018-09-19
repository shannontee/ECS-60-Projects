#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "StackLi.h"
#include "vector.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "CPUTimer.h"

using namespace std;

vector<CursorNode <int> > cursorSpace(500001);

int getChoice()
{

  int choice;
  
  do
  {
    cout << "\n      ADT Menu\n"; 
    cout << "0. Quit\n1. LinkedList\n2. CursorList\n";
    cout << "3. StackAr\n4. StackLi\n5. QueueAr\n";
    cout << "6. SkipList\nYour choice >> ";
    cin >> choice;

    if(choice < 0 || choice > 6)
      cout << "Your choice is not between 0 and 6.\n Please try again.";

  } while(choice < 0 || choice > 6);

  return choice;
}

void RunList(char* filename)
{
  char c;
  int num;
  char temp[500];
  List<int> List; // constructor
  ListItr<int> itr = List.zeroth();
  ifstream inf(filename); 

  inf.getline(temp, 500);

  while(inf >> c)
  {
    if(c == 'i')
    {
      inf >> num;
      List.insert(num,itr);
    }

    if(c == 'd')
    {
      inf >> num;
      List.remove(num); //every number that tries to delete will be in the list
    }
  }
  inf.close();
}

void RunCursorList(char* filename)
{
  char c;
  int num;
  char temp[500];
  CursorList<int> cursorList(cursorSpace);
  CursorListItr<int> cursorItr = cursorList.zeroth();
  ifstream inf(filename);

  inf.getline(temp, 500);
  
  while(inf >> c)
  {
    if(c == 'i')
    {
      inf >> num;
      cursorList.insert(num,cursorItr);
    }

    if(c == 'd')
    {
      inf >> num;
      cursorList.remove(num); //every number that tries to delete will be in the list
    }
  }
  inf.close();
}

void RunStackAr(char* filename)
{
  char c;
  int num;
  char temp[500];
  StackAr<int> stackArray(500001);
  
  ifstream inf(filename);
  inf.getline(temp,500);

  while(inf >> c)
  {
    if(c == 'i')
    {
      inf >> num;
      stackArray.push(num);
    }

    if(c == 'd')
    {
      inf >> num;
      stackArray.pop();
    }
  }
  inf.close();
}

void RunStackLi(char* filename)
{
  char c;
  int num;
  char temp[500];
  StackLi<int> stackList;

  ifstream inf(filename);
  inf.getline(temp,500);

  while(inf >> c)
  {
    if(c == 'i')
    {
      inf >> num;
      stackList.push(num);
    }

    if(c == 'd')
    {
      inf >> num;
      stackList.pop();
    }
  }
  inf.close();
}

void RunQueueAr(char* filename)
{
  char c;
  int num;
  char temp[500];
  Queue<int> queueArray(5000000);

  ifstream inf(filename);
  inf.getline(temp,500);

  while(inf >> c)
  {
    if(c == 'i')
    {
      inf >> num;
      queueArray.enqueue(num);
    }

    if(c == 'd')
    {
      inf >> num;
      queueArray.dequeue();
    }
  }
  inf.close();
}

void RunSkipList(char* filename)
{
  char c;
  int num;
  char temp[500];
  SkipList<int> skipList(0, 500000);
  ifstream inf(filename);

  inf.getline(temp, 500);

  while(inf >> c)
  {
    if(c == 'i')
    {
      inf >> num;
      skipList.insert(num);
    }
   
    if(c == 'd')
    {
      inf >> num;
      skipList.deleteNode(num); 
    }
  }
  inf.close();
}

int main ()
{
  char filename[80];
  int choice;
  CPUTimer ct;

  cout << "Filename >> ";
  cin >> filename;
  
  do
  {
    choice = getChoice();
    ct.reset();
    switch (choice)
    {
      case 1: RunList(filename); break;
      case 2: RunCursorList(filename); break;
      case 3: RunStackAr(filename); break;
      case 4: RunStackLi(filename); break;
      case 5: RunQueueAr(filename); break;
      case 6: RunSkipList(filename); break;
    }

    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while (choice > 0);

  return 0;

} //main()
