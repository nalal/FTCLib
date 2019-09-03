// Header include
#include "thread.h"

using std::thread;
using std::this_thread;
using std::string;
using std::cout;

const int threads = thread::hardware_concurrency();
int usedThreads = 0;
threadInfo threadList[(threads - 1)];

//Incomplete
void stripeThreadRaw(void (*func))
{
	for(uint8_t i = 0; i < threads; i++)
	{
		thread().detach;
	}
	while(usedThreads > 0)
	{
		this_thread::sleep_for(std::chrono::seconds(1))
	}
}

//Incomplete
void setThreads()
{
	for(uint8_t i = 0; i < threads; i++)
	{
		threadInfo threadDetail;
		threadList[i] = threadDetail;
	}
}

//Get total threads
int getThreads()
{
	return threads();
}

//Get total used threads
int getThreadsUsed()
{
	return usedThreads;
}

//Print thread status
void printThreadInfo()
{
	threadInfo threadDetail;
	for(uint8_t i = 0; i < threads; i++)
	{
		threadDetail = threadList[i];
		cout << "THREAD: " << threadDetail.threadID << "\n" <<
			"THREAD USED: " << to_string(threadDetail.threadActive) <<
			"\n";
	}
}

