//Header include
#include "fileIO.h"

//Namespaces
using namespace std;
namespace fs = std::experimental::filesystem;

uint8_t mFiles = 0;
uint8_t mFilesMoved = 0;
uint8_t cFiles = 0;
uint8_t cFilesMoved = 0;

// Initializes directories for program from string vector
void initFiles(vector<string> DIRs)
{
	for(vector<string>::iterator it = DIRs.begin(); it != DIRs.end(); ++it)
	{
		string dir = *it;
		if(fs::exists(dir))
		{
			cout << "=Directory '" << dir << "' found.\n";
		}
		else
		{
			cout << "=Directory '" << dir << "' does not exist, creating.\n";
			fs::create_directories(dir);
		}
	}
}

// Removes file from folder if exists
void deleteFile(string file)
{
	if(fs::exists(file))
	{
		cout << " =Removing " << file << "\n";
		remove(file.c_str());
	}
}

// Copy function
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
		cout << "=File " << path << " does not exist.\n"
		mFilesMoved++;
	}
}

// Check if file exists
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
