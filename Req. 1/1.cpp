#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>

// Separate angle so the star can rotate independently from the cube.
float req1StarAngle = 0.0f;

// Translation values place the star beside the cube.
float StarX = 1.70f;
float StarY = 0.0f;
float StarZ = 0.0f;

// Draws a flat five-point star facing the camera.
void drawReq1Star()
{
    glPushMatrix();

    // Translate first so the star rotates around its own center at this
    // position instead of orbiting around the center of the scene.
    glTranslatef(
        StarX,
        StarY,
        StarZ
    );

    // Z-axis rotation is best for a flat star facing the camera.
    glRotatef(
        req1StarAngle,
        0.0f,
        0.0f,
        1.0f
    );

    // Gold color for the star. The normal also prepares its front face
    // for lighting if lighting is added in a later requirement.
    glColor3f(1.0f, 0.75f, 0.10f);
    glNormal3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);

        // Center of the star
        glVertex3f( 0.000f,  0.000f, 0.0f);

        // Alternating outer and inner points, starting at the top
        glVertex3f( 0.000f,  0.750f, 0.0f);
        glVertex3f( 0.206f,  0.283f, 0.0f);
        glVertex3f( 0.713f,  0.232f, 0.0f);
        glVertex3f( 0.333f, -0.108f, 0.0f);
        glVertex3f( 0.441f, -0.607f, 0.0f);
        glVertex3f( 0.000f, -0.350f, 0.0f);
        glVertex3f(-0.441f, -0.607f, 0.0f);
        glVertex3f(-0.333f, -0.108f, 0.0f);
        glVertex3f(-0.713f,  0.232f, 0.0f);
        glVertex3f(-0.206f,  0.283f, 0.0f);

        // Repeat the first outer point to close the fan
        glVertex3f( 0.000f,  0.750f, 0.0f);

    glEnd();

    glPopMatrix();
}

// Called by the starter program's existing timer callback.
void updateReq1StarRotation()
{
    req1StarAngle += 1.0f;

    if (req1StarAngle >= 360.0f)
    {
        req1StarAngle = 0.0f;
    }
}

