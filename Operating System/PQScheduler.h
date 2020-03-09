#pragma once

#include <vector>
#include <iostream>

class PriorityQ;
class Process;
class CPU;


class PQScheduler
{

public:
	int queues = 0; //The number of queues in the Scheduler
	int baseQuant = 0; //The base quantum of the Priority Queue
	int rtQuant = 0; //The real-time quantum of the Priority Queue
	int niceLimit = 0; //The Nice Limit
	std::vector<PriorityQ*> PQueues = std::vector<PriorityQ*>(); //The list of the priority queues
	int RTwait = 0; //The real time wait time
	int NRTwait = 0; //The non real time wait time
	int mitigated = 0;

	//Creates the Priority Queue Scheduler
	PQScheduler(int queues, int baseQuant, int rtQuant, int niceLimit);

	//Add process to the Priority Queues
	virtual void newProcess(Process *newProc);

	//Schedules the processes throughout the PQ's
	virtual void schedule(std::vector<CPU*> &cpUref, int cpUs, int schedStrat, int preemption, int clock, int mitigation, int pqBurstLimit);

	//Reqchedules the cpu's if the quantum has been exceeded
	virtual void reschedule(std::vector<CPU*> &cpUref, int cpUs, int schedStrat, int clock);

	//Reports the Priority Queue Scheduler
	virtual void report();
};
