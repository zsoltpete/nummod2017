#include "graphicalhelper.h"

double winWidth = 800, winHeight = 800;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	setColor(red);
	Matrix poligonPoints = drawPoligon(20, vec2(400,400), 200);
	drawAllDiagonal(poligonPoints, blue, green);
	glutSwapBuffers();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Drag & Drop");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}