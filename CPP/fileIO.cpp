//Header include
#include "fileIO.h"

//Namespaces
using namespace std;
namespace fs = std::experimental::filesystem;

uint8_t mFiles = 0;
uint8_t mFilesMoved = 0;
uint8_t cFiles = 0;
uint8_t cFilesMoved = 0;

// Initializes directories for program
void initFiles(vector<string> DIRs)
{
	// Need to actually add this, needs to be rewritten from original form
}

// Removes mod from folder if exists
void deleteFile(string file)
{
	if(fs::exists(file))
	{
		cout << " =Removing " << file << "\n";
		remove(file.c_str());
	}
}

// Mod install function for threading
void copyFile(string path, string targ)
{
	if fs::exists(path)
	{
		fs::copy(path, targ, 
			fs::copy_options::overwrite_existing | fs::copy_options::recursive);
			cout << " =" << path << " moved." << endl;
		mFilesMoved++;
	}
	else
	{
		cout << "File " << path << " does not exist.\n"
		mFilesMoved++;
	}
}

// Check for mods and configs folder
int testDIR(string DIR)
{
	if(!fs::exists(DIR))
	{
		return 1;
	}
	return 0;
}


// Check if list file exists in old list folder
bool fileExists(string path)
{
	if(fs::exists(path))
	{
		return true;
	}
	else
	{
		return false;
	}
}
