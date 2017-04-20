//reader.h

#include <vector>

#ifndef OBJREADER_H
#define OBJREADER_H

#define MAX_VERT 100000

struct Vertex {

	double x;
	double y;
	double z;

};

struct Range {

	double maxOfX;
	double maxOfY;
	double maxOfZ;

};

struct EntityComp {
	int coord;
	EntityComp(int coord) { this->coord = coord; }
	bool operator()(const Vertex& v1, const Vertex& v2) const {
		if (coord == 1)
			return v1.x < v2.x;
		else if (coord == 2)
			return v1.y < v2.y;
		else if (coord == 3)
			return v1.z < v2.z;
	}
};


class Reader {
private:
		std::vector<Vertex> vectorOfVertex;
		std::vector<std::vector<int>> vectorOfFace;
		Range range;
public:
	Reader();
	~Reader();

	void load(const char* fileName);
	void draw(int colorMode);
	void findViewRange();
	int getSizeOfVertex();
	Range getRange();
	void clearVector();
};

#endif