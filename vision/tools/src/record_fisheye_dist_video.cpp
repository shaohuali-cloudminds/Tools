#include <cstdlib>
#include <iostream>
#include "fisheye.hpp"

using namespace std;
using namespace vision_tools;

int main(int argc, char** argv) {
	if(argc < 3) {
		cerr << "Invalid number of arguments" << endl;
		cerr << "Usage: ./record_fisheye_dist_video dev_id output_file_name" << endl;
		return -1;
	}

	int dev_id = atoi(argv[1]);
	Fisheye fisheye_obj(dev_id);
	fisheye_obj.record_distorted_video(argv[2]);
	return 0;
}
