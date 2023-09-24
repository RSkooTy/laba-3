#include "bonus.h"
#include <GL/freeglut.h>

void bonus::PrintCell(int x, int y, bool frame) {
    Cell::PrintCell(x, y, frame);
    double y_up, y_down, x_left, x_right;
    y_up = 1.0 - (double)y / board_size * 2;
    y_down = 1.0 - (double)(y + 1) / board_size * 2;
    x_left = (double)x / board_size * 2 - 1.0;
    x_right = (double)(x + 1) / board_size * 2 - 1.0;

    y_up -= 0.04;
    y_down += 0.04;
    x_left += 0.04;
    x_right -= 0.04;

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x_left, y_up);
    glVertex2f(x_left, y_down);
    glVertex2f(x_right, y_down);
    glVertex2f(x_right, y_up);
    glEnd();
}