#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "fisheye.hpp"
#include "directory.hpp"

using namespace std;
using namespace cv;
using namespace vision_tools;
using namespace io_tools;

int main(int argc, char** argv) {
	if(argc < 7) {
		cerr << "Invalid number of arguments"<< endl;
		cerr << "Usage: ./calibrate_fisheye device_id num_images cross_per_row "
				<< "cross_per_col input_folder_name output_file_name" << endl;
		return -1;
	}
	int dev_id = atoi(argv[1]);
	int img_num = atoi(argv[2]);
	int cross_per_row = atoi(argv[3]);
	int cross_per_col = atoi(argv[4]);
	string infile_folder = argv[5];
	string outfile = argv[6];
	Fisheye fisheye_obj(dev_id);
	cv::Size size(cross_per_row, cross_per_col);
	
	vector<string> file_names;
	get_dir_files(infile_folder, file_names);	
	for(int i = 0; i < file_names.size(); ++i) {
		file_names[i] = infile_folder + file_names[i];
		cout << file_names[i] << endl;
	}
	fisheye_obj.calibrate(img_num, size, file_names, outfile);
	return 0;
}
