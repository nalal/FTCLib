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
void downloadFromList(std::vector<std::string> urls, std::string list);
int downloadList(std::string url);
std::string getName(std::string link);
