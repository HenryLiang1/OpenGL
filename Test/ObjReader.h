//reader.h

#include <vector>

#ifndef OBJREADER_H
#define OBJREADER_H

struct Vertex {
	double x;
	double y;
	double z;
};

struct Ortho {
	double maxOfX;
	double maxOfY;
	double maxOfZ;
	double fitRange;
};

struct ElememtCMP {
	int coord;

	ElememtCMP(int coord) {
		this->coord = coord; 
	}

	bool operator()(const Vertex& v1, const Vertex& v2) const {
		if (coord == 1)
			return abs(v1.x) > abs(v2.x);
		else if (coord == 2)
			return abs(v1.y) > abs(v2.y);
		else if (coord == 3)
			return abs(v1.z) > abs(v2.z);
	}
};


class Reader {
private:
		std::vector<Vertex> vectorOfVertex;
		std::vector<std::vector<int>> vectorOfFace;
		Ortho ortho;
public:
	Reader();
	~Reader();

	bool load(const char* fileName);
	void draw(int colorMode);
	void findViewRange();
	int getSizeOfVertex();
	Ortho getOrtho();
	void clearVector();
};

#endif