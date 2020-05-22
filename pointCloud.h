// pointCloud.h
// pointCloud class for destructive scanner

using namespace std;

struct BSPoint
{
	float x;
	float y;
	float z;

	unsigned char r;
	unsigned char g;
	unsigned char b;

	BSPoint(int _x, int _y, int _z,
		unsigned char _r, unsigned char _g, unsigned char _b) {
		x = (float)_x;
		y = (float)_y;
		z = (float)_z;

		r = _r;
		g = _g;
		b = _b;
	}

	bool operator ==(const BSPoint &p) const {
		if (x == p.x && y == p.y && z == p.z)
			return true;
		return false;
	}

	bool operator !=(const BSPoint &p) const {
		if (x == p.x && y == p.y && z == p.z)
			return false;
		return true;
	}

	bool operator <(const BSPoint &p) const {
		if (z < p.z)return true;
		else if (z > p.z)return false;
		else if (y < p.y)return true;
		else if (y > p.y)return false;
		else if (x < p.x)return true;
		else 
			return false;
	}
};

class PointCloud
{
public:
	PointCloud();
	~PointCloud();

	unsigned char saveToPLYFile(const char* filename);
	void addPoint(BSPoint point);
	void clearAll();
	void sort();

private:
	list<BSPoint> points;
};
