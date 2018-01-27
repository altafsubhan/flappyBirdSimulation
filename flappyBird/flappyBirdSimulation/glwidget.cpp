#include "glwidget.h"
#include <cmath>
#include <iostream>

using namespace std;

const double BIRD_BELLY_RAD = 0.075;
const double POLE_WIDTH = 0.15;
double birdStartingX = -0.9 + BIRD_BELLY_RAD, birdStartingY = 0.4;
double bottomHeight = 0.8, gap = 0.45;
double poleRightX = 1;
int poleNum = 0;

void drawRect(GLdouble xRight, GLdouble yTop, GLdouble width, GLdouble height)
{
    glBegin(GL_QUADS);
        glVertex2d(xRight, yTop);
        glVertex2d(xRight, yTop - height);
        glVertex2d(xRight - width, yTop - height);
        glVertex2d(xRight - width, yTop);
    glEnd();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius)
{
    int i;
    int triangleAmount = 50;

    GLfloat twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(
                    x + (radius * cos(i *  twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
    glEnd();
}

void drawBird()
{
    //body
    glColor3f(1,0,0);
    drawFilledCircle(birdStartingX, birdStartingY, BIRD_BELLY_RAD);
    //wing
    glColor3f(0, 1, 0);
    drawFilledCircle(birdStartingX - 0.01, birdStartingY - 0.025, 0.011);
    drawRect(birdStartingX - 0.01, birdStartingY - 0.014, 0.065, 0.0215);
    drawFilledCircle(birdStartingX - 0.075, birdStartingY - 0.025, 0.011);
    //mouth
    glColor3f(255, 255, 0);
    drawRect(birdStartingX + 0.09, birdStartingY - 0.008, 0.05, 0.032);
    drawFilledCircle(birdStartingX + 0.04, birdStartingY - 0.024, 0.018);
    drawFilledCircle(birdStartingX + 0.09, birdStartingY - 0.016, 0.009);
    drawFilledCircle(birdStartingX + 0.09, birdStartingY - 0.032, 0.009);
    glColor3f(0,0,0);
    drawRect(birdStartingX + 0.0975, birdStartingY - 0.024, 0.07, 0.0025);
    //eye
    drawFilledCircle(birdStartingX + 0.05, birdStartingY + 0.024, 0.016);
}

void drawPole(int poleNo)
{
    glColor3f(0,255,0);
    drawRect(poleRightX, 1, POLE_WIDTH, 2 - bottomHeight - gap);    //top
    drawRect(poleRightX, -1 + bottomHeight, POLE_WIDTH, bottomHeight);  //bottom
}

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    //control speed of the bird
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(5);
}

void GLWidget::initializeGL()
{
    //background color
    glClearColor(0.53, 0.81, 0.98, 0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);   //needed to apply background color

    drawBird();
    drawPole(0);

    poleRightX -= 0.006;
    if (birdStartingY > -0.93)
    {
        //control movement of the bird
        birdStartingX += 0.006;
        birdStartingY -= 0.009;
    } else {
        birdStartingX += 0;
        birdStartingY += 0;
    }
}

void GLWidget::resizeGL(int w, int h)
{
}

