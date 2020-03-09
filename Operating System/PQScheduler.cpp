#include "PQScheduler.h"
#include "PriorityQ.h"
#include "Process.h"
#include "CPU.h"

PQScheduler::PQScheduler(int queues, int baseQuant, int rtQuant, int niceLimit)
{
	//Initialize the PQScheduler values
	this->queues = queues;
	this->baseQuant = baseQuant;
	this->rtQuant = rtQuant;
	this->niceLimit = niceLimit;

	PriorityQ tempVar(rtQuant, 0);
	PQueues.push_back(&tempVar); //Initiaze the real-time value

	for (int i = 1; i < queues; i++)
	{ //Initialize the non-real time PQueues
		PriorityQ tempVar2((baseQuant * i), i);
		PQueues.push_back(&tempVar2);
	}
}

void PQScheduler::newProcess(Process *newProc)
{ // If real-time (R), add to the real time PQ
	if (newProc->Ptype == L'R' && PQueues[0] != nullptr)
	{
		PQueues[0]->enqueue(newProc);
	}

	else if (newProc->Ptype == L'N' && PQueues[1] != nullptr)
	{ //If not, add to the new non-real time PQ
		PQueues[1]->enqueue(newProc);
	}
}

void PQScheduler::schedule(std::vector<CPU*> &cpUref, int cpUs, int schedStrat, int preemption, int clock, int mitigation, int pqBurstLimit)
{
	if (mitigation != 0 && clock % mitigation == 0)
	{
		for (int i = (PQueues.size() - 1); i > 0; i--)
		{ //Throughout each of the PQ's
			for (int cp = 0; cp < cpUref.size(); cp++)
			{ //The cpu's will be inserted and processes will be assigned to queues
				if (cpUref[cp]->empty() && PQueues[i]->giveHead() != nullptr)
				{
					cpUref[cp]->newProcess(PQueues[i]->dequeue(), PQueues[i]->Quantum);
				}
			}
			if (PQueues[i]->Queue->size() != 0)
			{
				mitigated++;
			}
		}
	}

	else
	{
		for (int i = 0; i < PQueues.size(); i++)
		{ //Throughout each of the PQ's
			for (int cp = 0; cp < cpUref.size(); cp++)
			{ //The cpu's will be inserted and processes will be assigned to queues
				if (cpUref[cp]->empty() && PQueues[i]->giveHead() != nullptr)
				{
					cpUref[cp]->newProcess(PQueues[i]->dequeue(), PQueues[i]->Quantum);
				}
			}
			if (PQueues[i]->Queue->size() != 0)
			{
				mitigated++;
			}
		}
	}
}

void PQScheduler::reschedule(std::vector<CPU*> &cpUref, int cpUs, int schedStrat, int clock)
{
	for (int i = 0; i < cpUref.size(); i++)
	{
		if (cpUref[i]->Qexceeded())
		{ //If the quantum time has been exceeded
			Process *newProc = cpUref[i]->CPUgiveP(); //CPU's processes
			int nextQueue = (newProc->isQueued() + 1); //Assign the cpu's down to the next queue

			if (nextQueue > PQueues.size() - 1)
			{ //Reiterates a queue back to the bottom queue if it's already at the bottom
				nextQueue = PQueues.size() - 1;
			}

			PQueues[nextQueue]->enqueue(newProc);
			cpUref[i]->newProcess(nullptr, 0);
		}
	}
}

void PQScheduler::report()
{
	for (int queue = 0; queue < PQueues.size(); queue++)
	{
		std::wcout << L"PriorityQ" << PQueues[queue]->myID << L" Quantum: " << PQueues[queue]->Quantum << L"	   head:" << PQueues[queue]->Qhead << L"	   tail:" << PQueues[queue]->Qtail << L"	   " << L"Queued=" << (PQueues[queue]->Qtail - PQueues[queue]->Qhead) << L"	longestwait=" << PQueues[queue]->longestQwait << L"	BurstsScheduled=" << PQueues[queue]->CountBurstsScheduled << std::endl;
	}
	std::wcout << L"Mitigation: " << mitigated << std::endl;
}
