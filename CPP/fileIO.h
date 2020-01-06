#pragma once

//C includes
#include <stdio.h>
#include <stdint.h>

//C++ includes
#include <experimental/filesystem>
#include <vector>

bool check_file(char * target_file);
void delete_file(char * target_file);
void copy_file(char * target_file, char * target_location);

