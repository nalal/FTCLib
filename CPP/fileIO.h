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

//Local includes
#include "download.h"

namespace fs = std::experimental::filesystem;

//Functions
void initFiles(std::vector<string> DIRs);
bool fileExists(std::string path);
void deleteFile(std::string file);
void copyFile(string path, string targ);
