//Defines
#define CURL_STATICLIB
#include "download.h"


using namespace std;

// Write function for download
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// Get name from URL, should move this to getting from headers
string getName(string link)
{
	size_t fileBranch = link.find_last_of("/");
	string name = link.substr(fileBranch+1);
	return name;
}

// Get link from list string
string getLink(string line)
{
	size_t fileBranch = line.find_first_of("~");
	string link = line.substr(fileBranch+1);
	fileBranch = link.find_first_of("~");
	link = link.substr(0,fileBranch);
	return link;
}

// Get type of file from list string
string getDLType(string line)
{
	size_t fileBranch = line.find_first_of("~");
	string type = line.substr(0, fileBranch);
	if(type.compare("mod") == 0)
	{
		type = "mods";
	}
	else if(type.compare("cfg") == 0)
	{
		type = "configs";
	}
	else if(type.compare("del") == 0)
	{
		type = "delete";
	}
	else
	{
		type = "invalid";
	}
	return type;
}

// Compare version of mod from cache to version from saved list
bool checkVer(string line, string list)
{
	size_t fileBranch = line.find_last_of("~");
	string ver = line.substr(fileBranch+1);
	//cout << "Getting modlist from " << listURL << endl;
	string link = getLink(line);
	string listName = "./modpacker/modList/" + getName(list);
	if(fs::exists(listName))
	{
		ifstream file(listName);
		string buffer;
		string inLine;
		//cout << "|Adding files to list." << endl;
		while(getline(file, buffer))
		{
			inLine = buffer;
			string inLink = getLink(inLine);
			if(inLink.compare(link) == 0)
			{
				size_t oFileBranch = inLine.find_last_of("~");
				string oVer = inLine.substr(oFileBranch+1);
				if(oVer.compare(ver) != 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}

// Reads headers
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    size_t numbytes = size * nitems;
    //printf("%.*s\n", numbytes, buffer);
    return numbytes;
}

// Download function
int curlExecute
(
	FILE *fp, 
	CURL *curl, 
	string modDir, 
	string link, 
	char outfilename[FILENAME_MAX]
)
{
	char *ct = NULL;
	if (curl)
	{
		curl = curl_easy_init();
		fp = fopen(outfilename,"wb");
		curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, -1L);
		curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
		return 0;
	}
	else
	{
		curl_easy_cleanup(curl);
		//cout << "CURL_ERROR is " << res << endl;
		return 1;
	}
}

// Get's list of lines and processes each
// Not implementing threading due to bandwidth conservation
void downloadFromList(vector<string> urls, string list)
{
	cout << "|Begining downloads." << endl;
	for(vector<string>::iterator it = urls.begin(); it != urls.end(); ++it)
	{
		string line = *it;
		string folder = getDLType(line);
		if(folder.compare("invalid") != 0 && folder.compare("delete") != 0)
		{
			if(checkVer(line, list))
			{
				string link = getLink(line);
				cout << " =Downloading " << getName(link) << " from " << link << 
				" to " << folder << endl;
				CURL *curl;
				FILE *fp;
				char outfilename[FILENAME_MAX];
				string modDir = "./modpacker/" + folder + "/" + getName(link);
				strcpy(outfilename, modDir.c_str());
				int res = curlExecute(fp, curl, modDir, link, outfilename);
				if(res == 0)
				{
					cout << " =" << outfilename << " downloaded." << endl;
				}
				else
				{
					cout << " =" << outfilename << " failed to download!" 
					<< endl; 
				}
			}
			else
			{
				cout << " -File " << getName(getLink(line)) << " already at"
				<< " correct version." << endl; 
			}
		}
		else if(folder.compare("delete") == 0)
		{
			string link = getLink(line);
			string file = getName(link);
			deleteMod(file);
		}
		else
		{
			cout << "-" << line << " is of an invalid type, skipping..." 
			<< endl;
		}
	}

}

// Download list from URL
int downloadList(string urls)
{
	string link = urls;
	cout << "Downloading " << getName(link) << " from " << link << endl;
	CURL *curl;
	FILE *fp;
	char outfilename[FILENAME_MAX];
	string modDir = "./modpacker/modListCache/" + getName(link);
	strcpy(outfilename, modDir.c_str());
	int res = curlExecute(fp, curl, modDir, link, outfilename);
	if(res == 1)
	{
		cout << "Failed to connect to given link!" << endl;
		return 1;
	}
	else
	{
		return 0;
	}
}
