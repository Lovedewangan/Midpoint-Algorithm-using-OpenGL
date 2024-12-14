#include <freeglut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread> 
#include <algorithm>


using namespace std;

struct Point {
    float x, y;
};

struct CirclePoint {
    int x, y;
};


vector<vector<Point>> ellipse;
vector<Point> currentEllipse;

vector<vector<Point>> circle;
vector<Point> currentCircle;

vector<CirclePoint> circleCoordinates;

bool isCircleFilled = false;
bool isEllipseFilled = false;

int rx;
int ry;

float xc;
float yc;

int xC;
int yC;
int radius;

float major;
float minor;

int factor = 0;
//vector<string> displayedCoordinates;


void renderBitmapString(float x, float y, void* font, const char* string) {
    glColor3f(0.0, 0.0, 0.0);
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void drawGrid() {
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(1.0);

    glBegin(GL_LINES);

    // Draw vertical grid lines
    for (float x = -100.0; x <= 100.0; x += 10.0) {
        glVertex2f(x, -100.0);
        glVertex2f(x, 100.0);
    }

    // Draw horizontal grid lines
    for (float y = -100.0; y <= 100.0; y += 9.0) {
        glVertex2f(-100.0, y);
        glVertex2f(100.0, y);
    }

    glEnd();
}

void drawGrid2() {
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(1.0);

    glBegin(GL_LINES);

    // Draw vertical grid lines
    for (float x = -100.0; x <= 100.0; x += 10.0) {
        glVertex2f(x, -100.0);
        glVertex2f(x, 100.0);
    }

    // Draw horizontal grid lines
    for (float y = -100.0; y <= 100.0; y += 9.0) {
        glVertex2f(-100.0, y);
        glVertex2f(100.0, y);
    }

    glEnd();
}



void ellipsePoints(int xc, int yc, int x, int y) {

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);

    glEnd();



    //glFlush();

    // Introduce a delay to make the drawing gradual


}

void circlePoints(int xc, int yc, int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);


    circleCoordinates.push_back({ xc + x, yc + y });
    circleCoordinates.push_back({ xc - x, yc + y });
    circleCoordinates.push_back({ xc + x, yc - y });
    circleCoordinates.push_back({ xc - x, yc - y });
    circleCoordinates.push_back({ xc + y, yc + x });
    circleCoordinates.push_back({ xc - y, yc + x });
    circleCoordinates.push_back({ xc + y, yc - x });
    circleCoordinates.push_back({ xc - y, yc - x });

    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);

    glEnd();
}



void drawEllipse(const Point& p1, const Point& p2) {


    xc = p1.x;
    yc = p1.y;



    rx = (abs(p2.x - p1.x)) + factor;
    ry = (abs(p2.y - p1.y)) + factor;

    cout << "Ellipse center: (" << xc << ", " << yc << ")" << endl;
    cout << "Major axis (rx): " << rx << endl;
    cout << "Minor axis (ry): " << ry << endl;

    float dx, dy, pk1, pk2, x, y;


    x = 0;
    y = ry;

    pk1 = (ry * ry) + (0.25 * rx * rx) - (rx * rx * ry);

    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy) {
        ellipsePoints(xc, yc, x, y);
        /*
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        glutPostRedisplay();
        */

        if (pk1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            pk1 = pk1 + dx + (ry * ry);

        }
        else {

            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);

            pk1 = pk1 + dx - dy + (ry * ry);
        }

    }

    pk2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    while (y >= 0) {

        ellipsePoints(xc, yc, x, y);
        /*
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        glutPostRedisplay();
        */

        if (pk2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            pk2 = pk2 + (rx * rx) - dy;


        }
        else {
            y--;
            x++;


            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            pk2 = pk2 + dx - dy + (rx * rx);
        }

    }




}

void drawCircle(const Point& p1, const Point& p2)
{
    xC = p1.x;
    yC = p1.y;
    radius = (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2))) + factor;

    int x = 0;
    int y = radius;
    int p = 1 - radius;

    circlePoints(xC, yC, x, y);

    while (x <= y)
    {
        x++;
        if (p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }
        circlePoints(xC, yC, x, y);
    }
}

void scanLineFill() {


    int yMin = yC - radius;
    int yMax = yC + radius;


    glColor3f(0.0, 1.0, 0.0);
    glPointSize(5.0f);

    for (int y = yMin; y <= yMax; y++) {




        int dy = y - yC;
        int dx = sqrt(radius * radius - dy * dy);

        int x1 = xC - dx;
        int x2 = xC + dx;








        for (int x = x1 + 1; x < x2; x++) {

            glBegin(GL_POINTS);
            glVertex2i(x, y);
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            glEnd();
            glFlush();

        }






    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glFlush();
}

void leftSubDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);


    drawGrid();

    for (const auto& e : ellipse) {
        if (e.size() == 2) {
            drawEllipse(e[0], e[1]);
        }
    }

    renderBitmapString(-45.0f, 90.0f, GLUT_BITMAP_HELVETICA_18, "Ellipse Generation Using Midpoint Algorithm");

    renderBitmapString(50.0f, -90.0f, GLUT_BITMAP_HELVETICA_12, "Love Dewangan 500109339");

    major = 2 * rx;
    minor = 2 * ry;
    char majorAxisStr[50];
    char minorAxisStr[50];

    sprintf_s(majorAxisStr, "Major Axis: %.2f", major);
    sprintf_s(minorAxisStr, "Minor Axis: %.2f", minor);
    renderBitmapString(-95.0f, -87.5f, GLUT_BITMAP_HELVETICA_12, majorAxisStr);
    renderBitmapString(-95.0f, -95.0f, GLUT_BITMAP_HELVETICA_12, minorAxisStr);

    char circleCenterCoordinates[50];
    sprintf_s(circleCenterCoordinates, "Center of Circle: (%.2f , %.2f)", xc, yc);
    renderBitmapString(-95.0f, -80.0f, GLUT_BITMAP_HELVETICA_12, circleCenterCoordinates);


    glFlush();

}

void rightSubDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);


    drawGrid2();
    for (const auto& c : circle) {
        if (c.size() == 2) {
            drawCircle(c[0], c[1]);
        }
    }

    /*scanLineFill();*/

    if (isCircleFilled) {
        scanLineFill();
    }

    renderBitmapString(-40.0f, 90.0f, GLUT_BITMAP_HELVETICA_18, "Circle Generation Using Midpoint Algorithm");
    renderBitmapString(50.0f, -90.0f, GLUT_BITMAP_HELVETICA_12, "Love Dewangan 500109339");

    major = 2 * rx;
    minor = 2 * ry;
    char radiusStr[50];


    sprintf_s(radiusStr, "Radius of Circle: %d", radius);
    renderBitmapString(-95.0f, -87.5f, GLUT_BITMAP_HELVETICA_12, radiusStr);

    char circleCenterCoordinates[50];
    sprintf_s(circleCenterCoordinates, "Center of Circle: (%d , %d)", xC, yC);
    renderBitmapString(-95.0f, -80.0f, GLUT_BITMAP_HELVETICA_12, circleCenterCoordinates);
    glFlush();
}



void mainWindowMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float x_pos = (x / (float)width) * 200.0f - 100.0f;
        float y_pos = ((height - y) / (float)height) * 200.0f - 100.0f;

        currentEllipse.push_back({ x_pos, y_pos });

        if (currentEllipse.size() == 2) {
            ellipse.push_back(currentEllipse);
            currentEllipse.clear();
        }

        glutPostRedisplay();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        ellipse.clear();
        currentEllipse.clear();
        glutPostRedisplay();
        factor = 0;

    }
    else if (button == 3) {
        factor += 1;

    }
    else if (button == 4) {
        factor -= 1;

    }

    glutPostRedisplay();
}


void subWindowMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int width = glutGet(GLUT_WINDOW_WIDTH);
        int height = glutGet(GLUT_WINDOW_HEIGHT);

        float x_pos = (x / (float)width) * 200.0f - 100.0f;
        float y_pos = ((height - y) / (float)height) * 200.0f - 100.0f;

        currentCircle.push_back({ x_pos, y_pos });

        if (currentCircle.size() == 2) {
            circle.push_back(currentCircle);
            currentCircle.clear();
        }

        glutPostRedisplay();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        circle.clear();
        currentCircle.clear();
        circleCoordinates.clear();
        glutPostRedisplay();
        factor = 0;
        isCircleFilled = false;
    }
    else if (button == 3) {
        factor += 1;

    }
    else if (button == 4) {
        factor -= 1;

    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (!isCircleFilled) {
        if (key == 102) {
            isCircleFilled = !isCircleFilled;
        }
    }
    else if (isCircleFilled) {
        if (key == 102) {
            isCircleFilled = !isCircleFilled;
        }
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    // Set the display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set the window size
    glutInitWindowSize(1600, 800);
    // Set the window position
    glutInitWindowPosition(100, 100);
    // Create the window with a title
    int mainWindow = glutCreateWindow("Ellipse and Circle Generation");
    glutDisplayFunc(display);
    init();


    //glutSetWindow(mainWindow);
    int leftSubWindow = glutCreateSubWindow(mainWindow, 0, 0, 800, 800);
    //glutSetWindow(leftSubWindow);
    init();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutDisplayFunc(leftSubDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(mainWindowMouse);



    int rightSubWindow = glutCreateSubWindow(mainWindow, 800, 0, 800, 800);

    init();
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glutDisplayFunc(rightSubDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(subWindowMouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
