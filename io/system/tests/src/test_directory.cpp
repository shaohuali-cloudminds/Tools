#include <iostream>
#include <vector>
#include <string>
#include "directory.hpp"

using namespace std;
using namespace io_tools;

int main(int argc, char** argv) {
	if(argc == 1) {
		cout << "Please specify folder" << endl;
		return -1;
	}
	vector<string> file_names;
	if (get_dir_files(argv[1], file_names)) {
		for(int i = 0; i < file_names.size(); ++i) {
			cout << file_names[i] << endl;
		}
	}
	return 0;
}
