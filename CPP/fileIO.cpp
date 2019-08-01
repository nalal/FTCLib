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
void initFiles()
{
	fs::path dir = fs::current_path();
	fs::path mods = "./modpacker/mods";
	fs::path configs = "./modpacker/configs";
	fs::path file = "./modpacker/packer";
	fs::path listDIR = "./modpacker/modList";
	fs::path listCacheDIR = "./modpacker/modListCache";
	if(fs::exists(file))
	{
		if(fs::exists(mods))
		{
			cout << " -Mods folder found." << endl;
			cout << " =Cleaning existing cache..." << endl;
			for(auto& p: fs::directory_iterator(mods))
			{
				cout<< " =Removing " << p << endl;
				fs::remove_all(p);
			}
		}
		else
		{
			cout << " -Mods folder not found." << endl;
			cout << " =Creating mods folder." << endl;
			fs::create_directory(mods);
		}
		if(fs::exists(configs))
		{
			cout << " -Configs folder found." << endl;
		}
		else
		{
			cout << " -Configs folder not found." << endl;
			cout << " =Creating configs folder." << endl;
			fs::create_directory(configs);
		}
		if(fs::exists(listDIR))
		{
			cout << " -List folder found." << endl;
		}
		else
		{
			cout << " -List folder not found." << endl;
			cout << " =Creating list folder." << endl;
			fs::create_directory(listDIR);
		}
		if(fs::exists(listCacheDIR))
		{
			cout << " -List cache folder found." << endl;
		}
		else
		{
			cout << " -List cache folder not found." << endl;
			cout << " =Creating list cache folder." << endl;
			fs::create_directory(listCacheDIR);
		}
	}
	else
	{
		cout << "Application file not found, please make certain that" << 
		" the file is located in the correct folder." << endl;
	}
}

// Removes mod from folder if exists
void deleteMod(string file)
{
	if(fs::exists("./mods/" + file))
	{
		string modDir = "./mods/";
		cout << " =Removing flagged mod " << file << endl;
		remove((modDir + file).c_str());
	}
}

// Mod install function for threading
void installMod(string path)
{
	fs::copy(path, "./mods", 
		fs::copy_options::overwrite_existing | fs::copy_options::recursive);
		cout << " =" << path << " moved." << endl;
	mFilesMoved++;
}

// Config install function for threading
void installCfg(string path)
{
	fs::copy(path, "./config", 
		fs::copy_options::overwrite_existing | fs::copy_options::recursive);
	cout << " =" << path << " moved." << endl;
	cFilesMoved++;
}

// Moves mod and config files into instance folders
void install()
{
	cout << "|Begining install." << endl;
	cout << " =Installing mods..." << endl;
	int maxThreads = thread::hardware_concurrency();
	cout << " -Striping opperations over " << maxThreads << " threads." << endl;
	for(auto& p: fs::directory_iterator("./modpacker/mods"))
	{
		cout <<" =Moving " << p << endl;
		if(maxThreads == 1)
		{
			installMod(p.path().string());
			mFiles++;
		}
		else
		{
			while((maxThreads - 1) == (mFiles - mFilesMoved))
			{
				this_thread::sleep_for(chrono::nanoseconds(100));
			}
			thread (installMod, p.path().string()).detach();
			mFiles++;
			cout << "  =Total threads in use " << (mFiles - mFilesMoved) << endl;
		}
	}
	while(mFiles != mFilesMoved)
	{
		this_thread::sleep_for(chrono::nanoseconds(100));
	}
	cout << " =Removing cached mods..." << endl;
	fs::remove_all("./modpacker/mods");
	cout << " =Installing configs..." << endl;
	for(auto& p: fs::directory_iterator("./modpacker/configs"))
	{
		if(maxThreads == 1)
		{
			installCfg(p.path().string());
			cFiles++;
		}
		else
		{
			while((maxThreads - 1) == (cFiles - cFilesMoved))
			{
				this_thread::sleep_for(chrono::nanoseconds(100));
			}
			cout <<" =Moving " << p << endl;
			thread (installCfg, p.path().string()).detach();
			cFiles++;
		}
	}
	while(cFiles != cFilesMoved)
	{
		this_thread::sleep_for(chrono::nanoseconds(100));
	}
	cout << " =Removing cached configs..." << endl;
	fs::remove_all("./modpacker/configs");
}

// This gets the list from a file on the web (can be plain text or actual file)
void getList(string listURL)
{
	cout << "Getting modlist from " << listURL << endl;
	string listName = "./modpacker/modListCache/" + getName(listURL);
	if(fs::exists(listName))
	{
		cout << " =Cleaning old list cache." << endl;
		remove(listName.c_str());
	}
	int res = downloadList(listURL);
	if(res == 0)
	{
		string currentList= "./modpacker/modList/" + getName(listURL);
		ifstream file(listName);
		vector<string> vStrings;
		string buffer;
		string line;
		cout << "|Adding files to list." << endl;
		while(getline(file, buffer))
		{
			line = buffer;
			cout << " =" << line << " added to download list." << endl;
			vStrings.push_back(line);
		}
		downloadFromList(vStrings, currentList);
		remove(currentList.c_str());
		fs::copy(listName, currentList);
		install();
	}
	else
	{
		cout << "|Ending program prematurely due to missing list" << endl;
	}
}

// Check for mods and configs folder
int testDIR()
{
	if(!fs::exists("./mods") || !fs::exists("./config"))
	{
		return 1;
	}
	return 0;
}


// Check if list file exists in old list folder
bool listExists()
{
	if(fs::exists("./modpacker/modList/*"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void save()
{
	cout << "This is supposed to save a file, but it's not done yet." << endl;
	// Actually it might not, I'm probably going to pull it
}
