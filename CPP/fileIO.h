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
void initFiles();
int testDIR();
bool listExists();
void deleteMod(std::string file);
void save();
void getList(std::string listURL);
