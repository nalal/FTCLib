#pragma once

//C includes
#include <stdio.h>
#include <stdint.h>

//C++ includes
#include <fstream>
#include <experimental/filesystem>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

//Local includes
#include "download.h"

namespace fs = std::experimental::filesystem;

//Functions
void initFiles(std::vector<string> DIRs);
int testDIR(std::string DIR);
bool fileExists(std::string path);
void deleteFile(std::string file);
void getList(std::string listURL);
