// CS0045 - Technical Assessment 2
// Requirement 3 - Complete ONE Visual Enhancement (Option A: Lighting Challenge)
//
// This builds on Requirement 2 (a continuously rotating 3D star) and adds a
// configurable light together with material properties so the surface is
// clearly shaded: it looks bright where it faces the light and dark where it
// faces away. As the star rotates (Requirement 2) the shading sweeps across
// the faces, which makes the lighting effect obvious.
//
// Module 8 concepts applied here:
//   GL_LIGHTING   - master switch that enables the lighting equation
//   GL_LIGHT0     - the single light source we configure
//   GL_AMBIENT    - base color seen even on unlit faces
//   GL_DIFFUSE    - main directional shading (brightest facing the light)
//   GL_SPECULAR   - the shiny highlight
//   GL_SHININESS  - how tight/focused that highlight is
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
void setupReq3Lighting();

GLuint VBOid = 0;
float req1StarAngle = 0.0f;
bool rotateObject = true;

// Requirement 3: lighting can be toggled so the visual change is easy to show.
bool lightingEnabled = true;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CS0045 - Req 3: Lit Rotating 3D Star");

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

// Requirement 3 (Option A): configure one light and the surface material.
// Changing any of these values clearly changes the rendered result.
void setupReq3Lighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Use glColor* values as the material color so the gold star keeps its hue
    // while still being shaded by the light.
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Light position (4th component 1.0 = positional light to the upper right).
    GLfloat lightPosition[] = { 2.0f, 2.0f, 3.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Ambient: dim base light so faces turned away are not fully black.
    GLfloat lightAmbient[]  = { 0.20f, 0.20f, 0.20f, 1.0f };
    // Diffuse: the main light that produces the bright/dark shading gradient.
    GLfloat lightDiffuse[]  = { 0.90f, 0.90f, 0.85f, 1.0f };
    // Specular: the color of the shiny highlight.
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Material: how the surface reflects the specular highlight, and how tight
    // that highlight is (GL_SHININESS, range 0-128).
    GLfloat matSpecular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 64.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  matSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

    // Normals are supplied per face by the VBO; keep them unit length after
    // any scaling so the shading stays correct.
    glEnable(GL_NORMALIZE);
}

void initialize()
{
    initializeVBO();
    initializeView();
    setupReq3Lighting();
    glClearColor(0.025f, 0.035f, 0.065f, 1.0f);
}

void drawReq1Star()
{
    glPushMatrix();
    // Tilt the star and spin around Y to reveal its front, back, and side faces.
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(req1StarAngle, 0.0f, 1.0f, 0.0f);

    // Gold color; with GL_COLOR_MATERIAL this becomes the ambient+diffuse
    // material so the lit star still looks gold.
    glColor3f(1.0f, 0.75f, 0.10f);
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
    // Space pauses or resumes the star's rotation (from Requirement 2).
    if (key == ' ')
    {
        rotateObject = !rotateObject;
    }
    // Requirement 3: 'L' toggles lighting so the visual enhancement is easy to
    // demonstrate side by side (lit vs. flat/unlit).
    else if (key == 'l' || key == 'L')
    {
        lightingEnabled = !lightingEnabled;
        if (lightingEnabled)
        {
            glEnable(GL_LIGHTING);
        }
        else
        {
            glDisable(GL_LIGHTING);
        }
        glutPostRedisplay();
    }
}
