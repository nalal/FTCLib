// Header include
#include "thread.h"

using std::thread;
using std::this_thread;

const int threads = hardware_concurrency();;
int usedThreads = 0;

void stripeThread()
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

int getThreads()
{
	return threads();
}

int getThreadsUsed()
{
	return usedThreads;
}
