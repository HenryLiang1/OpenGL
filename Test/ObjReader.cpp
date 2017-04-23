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

bool Reader::load(const char* fileName)
{
	std::ifstream objFile;
	objFile.open(fileName);

	if (!objFile){
		printf("Failed to open the file !\n");
		return false;
	}
	else{
		clearVector();
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
	return true;
}

void Reader::draw(int colorMode)
{
	for (int i = 0; i < vectorOfFace.size(); i++){
		float r = 0.0;
		float g = 1.0;
		float b = 0.0;

		if (colorMode == 2){
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}

		glColor3f(r, g, b);
		glBegin(GL_POLYGON);
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

Ortho Reader::getOrtho(){
	return ortho;
}

void Reader::clearVector(){
	vectorOfVertex.clear();
	vectorOfFace.clear();
}

void Reader::findViewRange(){
	std::vector<Vertex> sortedVectorOfVertex(vectorOfVertex);
	std::sort(sortedVectorOfVertex.begin(), sortedVectorOfVertex.end(), ElememtCMP(1));
	ortho.maxOfX = abs(sortedVectorOfVertex[0].x);
	
	std::sort(sortedVectorOfVertex.begin(), sortedVectorOfVertex.end(), ElememtCMP(2));
	ortho.maxOfY = abs(sortedVectorOfVertex[0].y);
	
	std::sort(sortedVectorOfVertex.begin(), sortedVectorOfVertex.end(), ElememtCMP(3));
	ortho.maxOfZ = abs(sortedVectorOfVertex[0].z);

	ortho.fitRange = std::max(ortho.maxOfX, ortho.maxOfY);
	
	/*std::cout << ortho.maxOfX << std::endl;
	std::cout << ortho.maxOfY << std::endl;
	std::cout << ortho.maxOfZ << std::endl;*/
}