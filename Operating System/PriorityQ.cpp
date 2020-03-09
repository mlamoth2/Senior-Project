#include "PriorityQ.h"
#include "Process.h"

PriorityQ::PriorityQ(int quantum, int ID)
{
   Quantum = quantum;
   Qhead = Qtail = Qwait = longestQwait = CountBurstsScheduled = 0;
   Queue = std::vector<Process*>(Qsize);
   myID = ID;
}

void PriorityQ::enqueue(Process *process)
{
   Queue[Qtail] = process;
   Queue[Qtail]->assignQueue(myID);
   Qtail++;
   if (Qtail > Qsize)
   {
	   Qtail = 1; //wrap the index around
   }
   CountBurstsScheduled++;
}

Process *PriorityQ::dequeue()
{
   int wasHead = Qhead;
   Qhead++;
   if (Qhead > Qsize)
   {
	   Qhead = 1; //wrap the index around
   }
   return (Queue[wasHead]);
}

Process *PriorityQ::giveHead()
{ //need and empty test
   if (Qhead != Qtail)
   {
	   return (Queue[Qhead]);
   }
   else
   {
	   return (nullptr);
   }
}

int PriorityQ::giveQuant()
{
	return Quantum;
}

int PriorityQ::givelongestQwait()
{
	return longestQwait;
}

int PriorityQ::setlongestQwait(int wait)
{
	return longestQwait = wait;
}

void PriorityQ::report()
{
}
