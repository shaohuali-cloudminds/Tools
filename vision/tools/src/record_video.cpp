#include <cstdlib>
#include <iostream>
#include "camera.hpp"

using namespace std;
using namespace vision_tools;

int main(int argc, char** argv) {
	if(argc < 3) {
		cerr << "Invalid number of arguments." << endl;
		cerr << "Usage: ./record_video dev_id video_name"	<< endl;
		return -1;
	}
	int dev_id = atoi(argv[1]);
	Camera cam_obj(dev_id);	
	cam_obj.record_video(argv[2]);
	return 0;
}
