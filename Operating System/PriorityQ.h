#pragma once

#include <vector>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
class Process;

// PriorityQ Class
class PriorityQ
{
   public:
   int Qhead = 0;
   int Qtail = 0;
   int Qwait = 0;
   int Quantum = 0;
   int longestQwait = 0;
   int CountBurstsScheduled = 0;
   int myID = 0;

   int Qsize = 100000;
   std::vector<Process*> Queue;

   //Constructor for new PriorityQ
   PriorityQ(int quantum, int ID);
   virtual void enqueue(Process *process);
   virtual Process *dequeue();
   virtual Process *giveHead();
   virtual int giveQuant();
   virtual int givelongestQwait();
   virtual int setlongestQwait(int wait);
   virtual void report();
}; //end of class Process
