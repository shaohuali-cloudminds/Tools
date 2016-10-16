#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "directory.hpp"

using namespace io_tools;

namespace io_tools {

bool get_dir_files(std::string dir, std::vector<std::string>& vec_files, 
		int scope) {
	DIR* dp;
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL) {
		std::cerr << "Error(" << errno << ") opening" << dir << std::endl;
		return false;
	}

	while((dirp = readdir(dp)) != NULL) {
		if(scope == WITHOUT_SELF_PARENT && 
				((std::string(dirp->d_name)) == "." || std::string(dirp->d_name) == "..")) {
			continue;
		}
		else {
			vec_files.push_back(std::string(dirp->d_name));
		}
	}

	closedir(dp);
	return true;
}

}
