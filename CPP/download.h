#pragma once
//C++ includes
#include <experimental/filesystem>

//C includes
#include <stdio.h>
#include <curl/curl.h>

namespace fs = std::experimental::filesystem;

//Functions

/* Download function
ex:
	download(
		[Name to save file as], 
		[Link to download file from], 
		[Print libcurl output to console]
	);

*/
void download(
	char * name, 
	char * link, 
	bool verbose = false
);

