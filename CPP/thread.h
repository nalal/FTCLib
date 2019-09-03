// C++ includes
#include <iostream>

// C includes
#include <thread.h>
#include <stdint.h>
#include <string.h>

// Local includes

// Objects
struct threadInfo
{
	std::thread threadID;
	char* threadTag;
	bool threadActive;
}

// Functions
int getThreadsUsed();
int getThreads();
void printThreadInfo();

// Vars

