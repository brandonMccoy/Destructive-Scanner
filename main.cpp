// main.cpp
// Main for destructive scanner

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include "pointCloud.h"

using namespace std;
using namespace cv;


struct coord3
{
	int x;
	int y;
	int z;

	coord3(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	bool operator ==(const coord3 &p) const {
		if (x == p.x && y == p.y && z == p.z)
			return true;
		return false;
	}

	bool operator !=(const coord3 &p) const {
		if (x == p.x && y == p.y && z == p.z)
			return false;
		return true;
	}
};

int main()
{
	PointCloud pc;

	int z = 0;
	int picNumber = 1;

	while(true)
	{
		Mat img = imread("imgs/d_" + to_string(picNumber++) + ".png");
		if (img.empty())
			break;

		// accept only char type matrices
		CV_Assert(img.depth() == CV_8U);

		const int channels = img.channels();
		if(channels == 3)
		{
			Mat_<Vec3b> _I = img;

			for (int i = 1; i < img.rows - 1; ++i) {
				for (int j = 1; j < img.cols - 1; ++j) {
					// The current pixel is not red
					if (_I(i, j)[0] != 0 && _I(i, j)[1] != 0 && _I(i, j)[2] != 255) {
						if (_I(i, j - 1)[0] == 0 && _I(i, j - 1)[1] == 0 && _I(i, j - 1)[2] == 255// left of current pixel

							|| _I(i - 1, j)[0] == 0 && _I(i - 1, j)[1] == 0 && _I(i - 1, j)[2] == 255// above current pixel

							|| _I(i, j + 1)[0] == 0 && _I(i, j + 1)[1] == 0 && _I(i, j + 1)[2] == 255// right of current pixel

							|| _I(i + 1, j)[0] == 0 && _I(i + 1, j)[1] == 0 && _I(i + 1, j)[2] == 255)// below current pixel
						{
							unsigned char r, g, b = 0;
							r = _I(i, j)[2];
							g = _I(i, j)[1];
							b = _I(i, j)[0];
							pc.addPoint(BSPoint(i, j, z, r, g, b));
						}
					}
				}
			}
		}

		z++;
	}

	pc.sort();

	pc.saveToPLYFile("results.ply");
	pc.clearAll();

	return 0;
}
