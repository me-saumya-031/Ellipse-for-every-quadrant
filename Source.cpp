#include <GL/glut.h>
#include <cmath>
#include <iostream>

int a = 100, b = 50;
int centerX = -100;
int centerY = -100;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
}

void plotSymmetryPoints(int x, int y) {
    glVertex2i(centerX + x, centerY + y);
    glVertex2i(centerX - x, centerY + y);
    glVertex2i(centerX - x, centerY - y);
    glVertex2i(centerX + x, centerY - y);
}

void drawEllipse() {
    int x = 0, y = b;
    float a2 = a * a, b2 = b * b;
    float fx = 0, fy = 2 * a2 * y;

    float p1 = b2 - (a2 * b) + (0.25 * a2);
    while (fx < fy) {
        plotSymmetryPoints(x, y);
        x++;
        fx += 2 * b2;

        if (p1 < 0) {
            p1 += b2 * (2 * x + 1);
        }
        else {
            y--;
            fy -= 2 * a2;
            p1 += b2 * (2 * x + 1) - a2 * (2 * y);
        }
    }

    float p2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y > 0) {
        plotSymmetryPoints(x, y);
        y--;
        fy -= 2 * a2;

        if (p2 > 0) {
            p2 += a2 * (1 - 2 * y);
        }
        else {
            x++;
            fx += 2 * b2;
            p2 += b2 * (2 * x) + a2 * (1 - 2 * y);
        }
    }
}

void drawGraph() {
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(1.0);

    glBegin(GL_LINES);
    glVertex2f(-200.0, 0.0);
    glVertex2f(200.0, 0.0);

    glVertex2f(0.0, -200.0);
    glVertex2f(0.0, 200.0);
    glEnd();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGraph();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    drawEllipse();
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "Enter the value of semi-major axis (a): ";
    std::cin >> a;
    std::cout << "Enter the value of semi-minor axis (b): ";
    std::cin >> b;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("4 Quadrants Graph with Ellipse");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
