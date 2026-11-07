// CS0045 - Technical Assessment 2: continuously rotating 3D star.
// Uses the starter's GLUT window, GLEW, VBO, camera, and timer callback.
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "star_lighting.h"

void initialize();
void display();
void animate(int value);
void keyboard(unsigned char key, int x, int y);
void drawReq1Star();
void updateReq1StarRotation();

GLuint VBOid = 0;
float req1StarAngle = 0.0f;
bool rotateObject = true;


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CS0045 - Rotating 3D Star");

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed.\n";
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(50, animate, 0);
    glutMainLoop();
    return 0;
}

void initializeVBO()
{
    initializeStarVBO(VBOid);
}

void initializeView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

void initialize()
{
    initializeVBO();
    initializeView();
    setupStarLighting();
    glClearColor(0.025f, 0.035f, 0.065f, 1.0f);
}

void drawReq1Star()
{
    glPushMatrix();
    // Tilt the star and spin around Y to reveal its front, back, and side faces.
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(req1StarAngle, 0.0f, 1.0f, 0.0f);
    drawStar(VBOid);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    drawReq1Star();
    glutSwapBuffers();
}

void updateReq1StarRotation()
{
    req1StarAngle += 1.0f;
    if (req1StarAngle >= 360.0f)
    {
        req1StarAngle -= 360.0f;
    }
}

// Requirement 2: advance the angle, request a redraw, and repeat the timer.
void animate(int /*value*/)
{
    if (rotateObject)
    {
        updateReq1StarRotation();
    }
    glutPostRedisplay();
    glutTimerFunc(50, animate, 0);
}

void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
    // Space pauses or resumes the star's rotation.
    if (key == ' ')
    {
        rotateObject = !rotateObject;
    }
}

