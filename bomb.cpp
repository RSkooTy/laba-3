#include "bomb.h"
#include <GL/freeglut.h>
void bomb::PrintCell(int x, int y, bool frame) {
	Cell::PrintCell(x, y, frame);
	double pi = 2 * acos(0.0);
	double R = (double)radius / (board_size * 5);
	double X = (double)(x + 0.5) * 2 / board_size - 1.0;
	double Y = 1.0 - (double)(y + 0.5) * 2 / board_size;
	int n = 25;
	glBegin(GL_POLYGON); 
	glColor3f(0.9f, 0.9f, 0.9f);
	for (int i = 0; i < n; ++i)
		glVertex2f(X + R * cos(2 * pi / n * i), Y + R * sin(2 * pi / n * i));
	glEnd();
}