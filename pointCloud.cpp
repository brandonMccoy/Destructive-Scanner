// pointCloud.cpp
// pointCloud class for destructive scanning

#include "pointCloud.h"

PointCloud::PointCloud()
{
	
}

PointCloud::~PointCloud()
{
}

unsigned char PointCloud::saveToPLYFile(const char* filename)
{
	ofstream plyFile;
	string plyFilename;

	plyFilename.assign(filename);

	plyFile.open(plyFilename.c_str());

	plyFile << "ply\n";
	plyFile << "format ascii 1.0\n";
	plyFile << "element vertex " << points.size() << "\n";;
	plyFile << "property float x\n";
	plyFile << "property float y\n";
	plyFile << "property float z\n";
	plyFile << "property uchar red\n";
	plyFile << "property uchar green\n";
	plyFile << "property uchar blue\n";
	plyFile << "element face 0\n";
	plyFile << "property list uchar int vertex_indices\n";
	plyFile << "end_header\n";

	for (list<BSPoint>::const_iterator iterator = points.begin(); iterator != points.end(); iterator++) {
		BSPoint p = *iterator;
		plyFile << p.x << " " << p.y << " " << p.z;
		plyFile << " " << (int)p.r << " " << (int)p.g << " " << (int)p.b << endl;
	}

	plyFile.close();
	return 0;
}

void PointCloud::addPoint(BSPoint point)
{
	points.push_back(point);
}

void PointCloud::clearAll()
{
	points.clear();
}

void PointCloud::sort()
{
	points.sort();
}
