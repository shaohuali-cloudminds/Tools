#include <cstdlib>
#include <iostream>
#include "fisheye.hpp"

using namespace std;
using namespace vision_tools;

int main(int argc, char** argv) {
	if(argc < 4) {
		cerr << "Invalid number of arguments" << endl;
		cerr << "Usage: ./record_fisheye_undist_video dev_id "
				 << "camera_model_file output_file_name" << endl;
		return -1;
	}

	int dev_id = atoi(argv[1]);
	Fisheye fisheye_obj(dev_id, argv[2]);
	fisheye_obj.record_undistorted_video(argv[3]);
	return 0;
}
