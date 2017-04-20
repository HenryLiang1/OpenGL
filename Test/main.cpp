#include "..\Dependencies\glew\glew.h"
#include "..\Dependencies\freeglew\freeglut.h"
#include "ObjReader.h"
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <Commdlg.h>

#define PI 3.14159265

const char* GOURD_FILE_PATH = "obj/gourd.obj"; 
const char* LAMP_FILE_PATH = "obj/lamp.obj";
const char* OCTAHEDRON_FILE_PATH = "obj/octahedron.obj";
const char* TEAPOT_FILE_PATH = "obj/teapot.obj";
const char* TEDDY_FILE_PATH = "obj/teddy.obj";
int colorMode = 1;
Reader reader;



class AffineTrans{
public:
	GLfloat tx = 0;
	GLfloat ty = 0;
	GLfloat tz = 0;
	int thetaX = 0;
	int thetaY = 0;
	int thetaZ = 0;
	int thetaArb = 0;
	void reset(){
		tx = 0;
		ty = 0;
		tz = 0;
		thetaX = 0;
		thetaY = 0;
		thetaZ = 0;
		thetaArb = 0;
	}
};

AffineTrans affine;

void drawGlobalAxis(){
	// draw line for x axis
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-10.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();
	// draw line for y axis
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glVertex3f(0.0, -10.0, 0.0);
	glEnd();
	// draw line for Z axis
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.0, -10.0);
	glEnd();

}

void drawLocalAxis(){
	// draw line for x axis
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.5, 0.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glEnd();
	// draw line for y axis
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 1.5, 0.0);
	glVertex3f(0.0, -1.5, 0.0);
	glEnd();
	// draw line for Z axis
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.5);
	glVertex3f(0.0, 0.0, -1.5);
	glEnd();
}


void renderScene(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10.0f, 0, 0, 0, 0, 1, 0);
	
	glPointSize(5);
	//ScaleMatrix(affine.tx, affine.ty, affine.tz);

	drawGlobalAxis();

	glTranslatef(affine.tx, affine.ty, 1.0);
	glRotatef(affine.thetaX, 1.0, 0.0, 0.0);
	glRotatef(affine.thetaY, 0.0, 1.0, 0.0);
	glRotatef(affine.thetaZ, 0.0, 0.0, 1.0);
	
	reader.draw(colorMode);
	

	
	drawLocalAxis();

	glFlush();
	glutSwapBuffers();

}

void setupRC()
{
	// Light values and coordinates
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { 0.f, 25.0f, 20.0f, 0.0f };
	// Enable lighting
	glEnable(GL_LIGHTING);
	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}

void changeSize(int w, int h){
	std::cout << "change size" << std::endl;
	reader.findViewRange();
	Range range = reader.getRange();
	//std::cout << range.maxOfX << std::endl;
	//std::cout << range.maxOfY << std::endl;
	//std::cout << range.maxOfZ << std::endl;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-range.maxOfX * 2, range.maxOfX * 2, -range.maxOfY * 2, range.maxOfY * 2, -200, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myKeyboard(unsigned char key, int x, int y){
	switch (key){
	case 'r': //reset
		std::cout << "r" << std::endl;
		affine.reset();
		break;
	case 'q': //rotation along x-axis
		std::cout << "q" << std::endl;
		affine.thetaX++;
		break;
	case 'a': //rotation along x-axis
		std::cout << "a" << std::endl;
		affine.thetaX--;
		break;
	case 'w': //rotation along y-axis
		std::cout << "w" << std::endl;
		affine.thetaY++;
		break;
	case 's': //rotation along y-axis
		std::cout << "s" << std::endl;
		affine.thetaY--;
		break;
	case 'e': //rotation along z-axis
		std::cout << "z" << std::endl;
		affine.thetaZ++;
		break;
	case 'd': //rotation along z-axis
		std::cout << "x" << std::endl;
		affine.thetaZ--;
		break;
	case 'z': //rotation along arbitrary-axis
		std::cout << "z" << std::endl;

		break;
	case 'x': //rotation along arbitrary-axis
		std::cout << "x" << std::endl;

		break;
	}
	std::cout << x << " " << y << std::endl;
	glutPostRedisplay();
}

void mySpecialKey(int key, int x, int y){
	switch (key){
	case GLUT_KEY_RIGHT:
		std::cout << "KEY_RIGHT" << std::endl;
		affine.tx++;
		break;
	case GLUT_KEY_LEFT:
		std::cout << "KEY_LEFT" << std::endl;
		affine.tx--;
		break;
	case GLUT_KEY_UP:
		std::cout << "KEY_UP" << std::endl;
		affine.ty++;
		break;
	case GLUT_KEY_DOWN:
		std::cout << "KEY_DOWN" << std::endl;
		affine.ty--;
		break;
	}

	glutPostRedisplay();

}

void myMouse(int button, int state, int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			int currentWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
			int currwntWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	
		}	
	}
}



enum MENU_TYPE
{
	MENU_FILE,
	MENU_RENDER_MODE,
	MENU_COLOR_MODE,
};

// Menu handling function definition
void mainMenu(int item)
{
	return;
}

void fileMenu(int item){
	reader.clearVector();
	switch (item){
	case 1:
		std::cout << "file 1" << std::endl;
		reader.load(GOURD_FILE_PATH);
		break;
	case 2:
		std::cout << "file 2" << std::endl;
		reader.load(LAMP_FILE_PATH);
		break;
	case 3:
		std::cout << "file 3" << std::endl;
		reader.load(OCTAHEDRON_FILE_PATH);
		break;
	case 4:
		std::cout << "file 4" << std::endl;
		reader.load(TEAPOT_FILE_PATH);
		break;
	case 5:
		std::cout << "file 5" << std::endl;
		reader.load(TEDDY_FILE_PATH);
		break;
	}
	changeSize(500, 500);
	glutPostRedisplay();
};
void renderMenu(int item){
	switch (item){
	case 1:
		std::cout << "point 1" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 2:
		std::cout << "line 2" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 3:
		std::cout << "face 3" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	glutPostRedisplay();
};
void colorsMenu(int item){
	switch (item){
	case 1:
		std::cout << "Single 1" << std::endl;
		colorMode = 1;
		break;
	case 2:
		std::cout << "random 2" << std::endl;
		colorMode = 2;
		break;
	}
	glutPostRedisplay();
};

void createMenu(void){
	GLint file, render, colors;
	file = glutCreateMenu(fileMenu);
	glutAddMenuEntry("Gourd", 1);
	glutAddMenuEntry("Lamp", 2);
	glutAddMenuEntry("Octahedron", 3);
	glutAddMenuEntry("Teapot", 4);
	glutAddMenuEntry("Teddy", 5);


	render = glutCreateMenu(renderMenu);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Face", 3);

	colors = glutCreateMenu(colorsMenu);
	glutAddMenuEntry("Single", 1);
	glutAddMenuEntry("Random", 2);

	glutCreateMenu(mainMenu);
	glutAddSubMenu("File", file);
	glutAddSubMenu("Render Mode", render);
	glutAddSubMenu("Colors Mode", colors);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);//optional
	glutInitWindowSize(500, 500); //optional
	glutCreateWindow("OpenGL First Window");
	setupRC();
	glEnable(GL_DEPTH_TEST);

	reader.load(GOURD_FILE_PATH);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKey);
	glutMouseFunc(myMouse);
	createMenu();
	glutMainLoop();

	return 0;
}
