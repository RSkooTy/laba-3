#include "element.h"
#include <GL/freeglut.h>
#include <cmath>


void Cell::color_analysis() {
    switch (color) {
    case Color::baby_blue:
        glColor3f(0.0f, 0.5f, 1.0f);
        break;
    case Color::blue_green:
        glColor3f(0.0f, 0.5f, 0.5f);
        break;
    case Color::dark_blue:
        glColor3f(0.0f, 0.2f, 0.3f);
        break;
    case Color::forest_green:
        glColor3f(0.0f, 0.3f, 0.0f);
        break;
    case Color::lilac:
        glColor3f(2.0f, 0.5f, 1.0f);
        break;
    case Color::black:
        glColor3f(0.0f, 0.0f, 0.0f);
        break;
    }
}

void Cell::PrintCell(int x, int y, bool frame) {
    double y_up, y_down, x_left, x_right;
    y_up = 1.0 - (double)y / board_size * 2;
    y_down = 1.0 - (double)(y + 1) / board_size * 2;
    x_left = (double)x / board_size * 2 - 1.0;
    x_right = (double)(x + 1) / board_size * 2 - 1.0;

    if (!frame) {
        y_up -= 0.01;
        y_down += 0.01;
        x_left += 0.01;
        x_right -= 0.01;
    }

    glBegin(GL_QUADS);
    color_analysis();
    glVertex2f(x_left, y_up);
    glVertex2f(x_left, y_down);
    glVertex2f(x_right, y_down);
    glVertex2f(x_right, y_up);
    glEnd();
}

