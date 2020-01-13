#pragma once
//C++ includes
#include <experimental/filesystem>

//C includes
#include <stdio.h>
#include <curl/curl.h>

namespace fs = std::experimental::filesystem;

//Functions
void download(
	char * name, 
	char * link, 
	bool verbose = false
);

