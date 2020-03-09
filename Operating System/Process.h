class Process
{
public:
	int id = 0; //process ID
	int size = 0; //Number of instructions
	int programCounter = 0; //program counter
	int diskStart = 0;
	int ramStart = 0;
	int priority = 0;
	int status = 0; //new, ready, waiting, etc.
	int inBuffSize = 0; //size of input buffer
	int outBuffSize = 0; //size of output buffer
	int tempBuff = 0; //size of temporary buffer
	int processLength = 0; //Total size of process including data/buffers
	int cpuID = 0;
	int age = 0; //Will record the age of the process to let lower priority processes run
	Clock *waitingClock;
	Clock *runningClock;
	double waitingTime = 0;
	double runningTime = 0;
	int operations = 0;
	double percentCache = 0;

	virtual ~Process()
	{
		delete waitingClock;
		delete runningClock;
	}

	Process(int id, int size, int programCounter, int diskStart, int ramStart, int priority, int processLength, int cpuID, Clock *waitingClock, Clock *runningClock, double waitingTime, double runningTime, int operations, double percentCache);

	virtual int getId();
	virtual int getSize();
	virtual int getProgramCounter();
	virtual int getPriority();

	virtual int getStatus();
	virtual void setStatus(int status);

	virtual int getInBuffSize();
	virtual int getOutBuffSize();
	virtual int getTempBuff();
	virtual int getProcessLength();
	virtual int getCpuID();
	virtual int getOperations();
	virtual double getPercentCache();
};
