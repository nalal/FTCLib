#pragma once
//C++ includes
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <experimental/filesystem>

//C includes
#include <stdio.h>
#include <curl/curl.h>

//Local includes
#include "fileIO.h"

namespace fs = std::experimental::filesystem;

//Functions
std::string getName(std::string link);
int curlExecute
(
	FILE *fp, 
	string link, 
	char outfilename[FILENAME_MAX],
	bool verbose
);
