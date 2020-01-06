//Header include
#include "fileIO.h"

//Namespaces
namespace fs = std::experimental::filesystem;
using std::vector

void copy_file(char * target_file, char * target_location)
{
	fs::copy(target_file,target_location);
}

void delete_file(char * target_file)
{
	fs::remove_all(target_file);
}

bool check_file(char * target_file)
{
	if(fs::exists(target_file))
		return true;
	else
		return false;
}

std::vector<char *> get_files(char * target_dir, int flag)
{

}
