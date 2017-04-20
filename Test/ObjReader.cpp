
#include "..\Dependencies\freeglew\freeglut.h"
#include "ObjReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>

Reader::Reader() {}

Reader::~Reader() {}

void Reader::load(const char* fileName)
{
	std::ifstream objFile;
	objFile.open(fileName);

	if (!objFile){
		printf("Failed to open the file !\n");
		return;
	}

	while (objFile.peek() != EOF){
		std::string line;
		while (std::getline(objFile, line))
		{
			std::stringstream ss(line);
			if (line[0] == 'v'){
				Vertex vertex;
				int i = 0;
				std::string arr[4];
				while (ss.good() && i <= 3) {
					ss >> arr[i++];
				}	
				vertex.x = atof(arr[1].c_str());
				vertex.y = atof(arr[2].c_str());
				vertex.z = atof(arr[3].c_str());

				vectorOfVertex.push_back(vertex);
			}
			else if (line[0] == 'f'){
				std::vector<int> points;
				char c;
				while (ss) {
					std::string p;
					ss >> p;
					if (isdigit(p[0])){
						//std::cout << p << " ";
						points.push_back(atoi(p.c_str()));
					}
				}
				vectorOfFace.push_back(points);
			}
		}
	}
	objFile.close();
	//show vertex
	/*for (int i = 0; i < vectorOfVertex.size(); i++){
		std::cout << i << ": " << vectorOfVertex[i].x << " " << vectorOfVertex[i].y << " " << vectorOfVertex[i].z << std::endl;
	}

	for (int i = 0; i < vectorOfFace.size(); i++){
		for (int j = 0; j < vectorOfFace[i].size(); j++){
			std::cout << vectorOfFace[i][j] << " ";
		}
		std::cout << std::endl;
	}*/

}

void Reader::draw(int colorMode)
{
	for (int i = 0; i < vectorOfFace.size(); i++){
		float r = 0.0;
		float g = 0.0;
		float b = 0.0;
		if (colorMode == 1){
			r = 0.0;
			g = 1.0;
			b = 0.0;
		}
		else if (colorMode == 2){
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
		glColor3f(r, g, b);
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < vectorOfFace[i].size(); j++){
			int indexOfVertex = vectorOfFace[i][j] - 1;
			glVertex3d(vectorOfVertex[indexOfVertex].x, vectorOfVertex[indexOfVertex].y, vectorOfVertex[indexOfVertex].z);
		}
		glEnd();
	}
}


int Reader::getSizeOfVertex(){
	return vectorOfVertex.size();
}

Range Reader::getRange(){
	return range;
}

void Reader::clearVector(){
	vectorOfVertex.clear();
	vectorOfFace.clear();
}

void Reader::findViewRange(){
	double maxX;
	double minX;
	double maxY;
	double minY;
	double maxZ;
	double minZ;
	
	std::vector<Vertex> sortedVectorOfVertex(vectorOfVertex);
	std::sort(sortedVectorOfVertex.begin(), sortedVectorOfVertex.end(), EntityComp(1));
	maxX = sortedVectorOfVertex[sortedVectorOfVertex.size() - 1].x;
	minX = sortedVectorOfVertex[0].x;
	
	std::sort(sortedVectorOfVertex.begin(), sortedVectorOfVertex.end(), EntityComp(2));
	maxY = sortedVectorOfVertex[sortedVectorOfVertex.size() - 1].y;
	minY = sortedVectorOfVertex[0].y;
	
	std::sort(sortedVectorOfVertex.begin(), sortedVectorOfVertex.end(), EntityComp(3));
	maxZ = sortedVectorOfVertex[sortedVectorOfVertex.size() - 1].z;
	minZ = sortedVectorOfVertex[0].z;
	
	std::cout << maxX << " " << minX << std::endl;
	std::cout << maxY << " " << minY << std::endl;
	std::cout << maxZ << " " << maxZ << std::endl;

	range.maxOfX = std::max(abs(maxX), abs(minX));
	range.maxOfY = std::max(abs(maxY), abs(minY));
	range.maxOfZ = std::max(abs(maxZ), abs(minZ));
	//std::cout << range.maxOfX;

	/*for (int i = 0; i < vectorOfVertex.size(); i++){
		std::cout << i << ": " << vectorOfVertex[i].x << " " << vectorOfVertex[i].y << " " << vectorOfVertex[i].z << std::endl;
	}*/
}