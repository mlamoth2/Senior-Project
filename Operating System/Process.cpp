#include "Process.h"

Process::Process(int id, int size, int programCounter, int diskStart, int ramStart, int priority, int processLength, int cpuID, Clock *waitingClock, Clock *runningClock, double waitingTime, double runningTime, int operations, double percentCache)
{
	this->id = id;
	this->size = size;
	this->programCounter = programCounter;
	this->diskStart = diskStart;
	this->ramStart = ramStart;
	this->priority = priority;
	this->status = 0;
	this->inBuffSize = 0;
	this->outBuffSize = 0;
	this->tempBuff = 0;
	this->processLength = processLength;
	this->cpuID = cpuID;
	this->waitingClock = waitingClock;
	this->runningClock = runningClock;
	this->waitingTime = waitingTime;
	this->runningTime = runningTime;
	this->operations = operations;
	this->percentCache = percentCache;
}

int Process::getId()
{
	return id;
}

int Process::getSize()
{
	return size;
}

int Process::getProgramCounter()
{
	return programCounter;
}

int Process::getPriority()
{
	return priority;
}

int Process::getStatus()
{
	return status;
}

void Process::setStatus(int status)
{
	this->status = status;
}

int Process::getInBuffSize()
{
	return inBuffSize;
}

int Process::getOutBuffSize()
{
	return outBuffSize;
}

int Process::getTempBuff()
{
	return tempBuff;
}

int Process::getProcessLength()
{
	return processLength;
}

int Process::getCpuID()
{
	return cpuID;
}

int Process::getOperations()
{
	return operations;
}

double Process::getPercentCache()
{
	return percentCache;
}
