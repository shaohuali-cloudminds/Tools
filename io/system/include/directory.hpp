#ifndef IO_SYSTEM_DIRECTORY_HPP_
#define IO_SYSTEM_DIRECTORY_HPP_

#include <vector>
#include <string>

namespace io_tools {

enum SCOPE {WITH_SELF_PARENT, WITHOUT_SELF_PARENT};

/**
 *  @brief Function to get file names in a directory, including '.' and '..'
 *
 *  @param dir Name of directory
 *  @param vec_files File names, in std::vector of strings
 *  @param 
 *
 *  @return Boolean, true for success, false for failure in openning directory
 */				
bool get_dir_files(const std::string dir, std::vector<std::string>& vec_files,
		int scope=WITHOUT_SELF_PARENT);

} // namespace io_tools

#endif // io/system/directory.hpp
