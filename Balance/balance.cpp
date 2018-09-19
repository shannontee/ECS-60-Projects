#include <iostream>
#include <fstream>
#include "StackLi.h"

using namespace std;

int main(int argc, char** argv)
{
  char readLine[500];
  char c;
  int num = 1;
  int i = 0;
  bool comment = false;

  StackLi<int> lineNum; 
  StackLi<char> stackList;

  ifstream inf(argv[1]);

  while(inf.getline(readLine, 500))
  {
    while(readLine[i])
    {
      if((readLine[i] == '{' || readLine[i] == '['|| readLine[i]  == '(') && !comment)
      {
        stackList.push(readLine[i]);
        lineNum.push(num);
      }
       if((readLine[i]  == ')'|| readLine[i] == ']'|| readLine[i]  == '}') && !comment)
      {
        if(stackList.isEmpty())
             cout << "Unmatched " << readLine[i] << " on line #" << num << endl;
    
        else if(!((stackList.top() =='{' && readLine[i]=='}') ||(stackList.top() =='(' && readLine[i]==')') || (stackList.top() =='[' && readLine[i]==']')))
        {
          c = stackList.top();
          cout << "Unmatched " << readLine[i] << " on line #" << num << endl;
          return 0;
        }
 
        else
          stackList.pop();
      }
      
     if(readLine[i]=='/' && readLine[++i] == '*')
     {  
       comment = true; 
       stackList.push('o'); // i call o my indicator for /*
       lineNum.push(num);
     }
      
     if (readLine[i] == '*')
     {
       i++;
       if (readLine[i] == '/')
       {
         comment = false; // no longer in comment mode
         if(stackList.isEmpty() )
         {
           cout << "Unmatched */ on line #" << num << endl;
           return 0;
          }
          else if (stackList.top() != 'o')
          {
            cout << "Unmatched " << stackList.top() << " on line #" << num << endl;
            return 0;
          }
          else
          {
            stackList.pop();
            lineNum.pop();
          }
        }
        else if(readLine[i] == '(' || readLine[i] == '{' || readLine[i] == '[')
        {
          stackList.push(readLine[i]);
          lineNum.push(num);
        }    
      }  
      i++;
    }
    num++;
    i = 0;
  }
  
  if(stackList.isEmpty())
    cout << "OK";
  else
  {
    if(stackList.top() == 'o')
      cout << "Unmatched /* on line #" << lineNum.top() << endl;
    else
      cout << "Unmatched " << stackList.top() << " on line #" << lineNum.top() << endl;
  }  

  inf.close();
  return 0;
}


