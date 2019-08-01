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

// Reads headers
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    size_t numbytes = size * nitems;
    return numbytes;
}

// Download function
int curlExecute
(
	FILE *fp, 
	string link, 
	char outfilename[FILENAME_MAX],
	bool verbose = false
)
{
	CURL *curl;
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
		if(verbose)
		{
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}
		else
		{
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		}
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
		return 0;
	}
	else
	{
		curl_easy_cleanup(curl);
		return 1;
	}
}
