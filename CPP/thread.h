// C++ includes

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
