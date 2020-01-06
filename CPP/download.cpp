//Defines
#define CURL_STATICLIB
#include "download.h"

size_t header_callback(
	char *buffer, 
	size_t size, 
	size_t nitems, 
	void *userdata
)
{
    size_t numbytes = size * nitems;
    //printf("%.*s\n", numbytes, buffer);
    return numbytes;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
}

void download(char * target, char * link, int season, bool verbose)
{
	FILE *fp;
	CURL *curl; 
	char *ct = NULL;
	char outfilename [65536];
	sprintf(
		outfilename, 
		"%s", 
		target
	);

	curl = curl_easy_init();
	fp = fopen(outfilename,"wb");

	curl_easy_setopt(curl, CURLOPT_URL, link);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, -1L);
	curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
	if(verbose)
	{
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	}
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	fclose(fp);
}
