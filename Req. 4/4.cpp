#define GLEW_STATIC

#include <cmath>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>

// These rotation variables are defined by the starter program and Req1.
extern float angle;
extern float req1StarAngle;

// Camera position starts at the same position as the starter camera.
float req4CameraX = 0.0f;
float req4CameraY = 0.0f;
float req4CameraZ = 5.0f;

// Zero yaw faces toward negative Z. Zero pitch looks straight ahead.
float req4CameraYaw = 0.0f;
float req4CameraPitch = 0.0f;

bool req4LightingEnabled = false;

const float REQ4_MOVE_STEP = 0.20f;
const float REQ4_LOOK_STEP = 3.0f;
const float REQ4_MAX_PITCH = 85.0f;
const float REQ4_DEGREES_TO_RADIANS = 0.0174532925f;

// Prepare one fixed-function light. It starts disabled and is controlled
// using the L key.
void initializeReq4Lighting()
{
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

// Rebuild the model-view matrix from the current camera state once per frame.
void applyReq4Camera()
{
    const float yawRadians =
        req4CameraYaw * REQ4_DEGREES_TO_RADIANS;

    const float pitchRadians =
        req4CameraPitch * REQ4_DEGREES_TO_RADIANS;

    const float directionX =
        std::sin(yawRadians) * std::cos(pitchRadians);

    const float directionY =
        std::sin(pitchRadians);

    const float directionZ =
        -std::cos(yawRadians) * std::cos(pitchRadians);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        req4CameraX,
        req4CameraY,
        req4CameraZ,
        req4CameraX + directionX,
        req4CameraY + directionY,
        req4CameraZ + directionZ,
        0.0f,
        1.0f,
        0.0f
    );
}

// Enable the configured light immediately before drawing the star.
void beginReq4StarLighting()
{
    if (!req4LightingEnabled)
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        return;
    }

    const GLfloat lightAmbient[] =
    {
        0.15f, 0.15f, 0.15f, 1.0f
    };

    const GLfloat lightDiffuse[] =
    {
        1.00f, 0.95f, 0.75f, 1.0f
    };

    const GLfloat lightPosition[] =
    {
        1.70f, 1.50f, 2.50f, 1.0f
    };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

// Prevent the star's lighting state from affecting the starter cube or any
// other object drawn afterward.
void endReq4StarLighting()
{
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void handleReq4Keyboard(unsigned char key)
{
    const float yawRadians =
        req4CameraYaw * REQ4_DEGREES_TO_RADIANS;

    // Forward direction on the XZ ground plane.
    const float forwardX = std::sin(yawRadians);
    const float forwardZ = -std::cos(yawRadians);

    // Right direction on the XZ ground plane.
    const float rightX = std::cos(yawRadians);
    const float rightZ = std::sin(yawRadians);

    switch (key)
    {
        case 'w':
        case 'W':
            req4CameraX += forwardX * REQ4_MOVE_STEP;
            req4CameraZ += forwardZ * REQ4_MOVE_STEP;
            break;

        case 's':
        case 'S':
            req4CameraX -= forwardX * REQ4_MOVE_STEP;
            req4CameraZ -= forwardZ * REQ4_MOVE_STEP;
            break;

        case 'a':
        case 'A':
            req4CameraX -= rightX * REQ4_MOVE_STEP;
            req4CameraZ -= rightZ * REQ4_MOVE_STEP;
            break;

        case 'd':
        case 'D':
            req4CameraX += rightX * REQ4_MOVE_STEP;
            req4CameraZ += rightZ * REQ4_MOVE_STEP;
            break;

        case 'q':
        case 'Q':
            req4CameraY -= REQ4_MOVE_STEP;
            break;

        case 'e':
        case 'E':
            req4CameraY += REQ4_MOVE_STEP;
            break;

        case 'u':
        case 'U':
            req4CameraPitch += REQ4_LOOK_STEP;

            if (req4CameraPitch > REQ4_MAX_PITCH)
            {
                req4CameraPitch = REQ4_MAX_PITCH;
            }
            break;

        case 'j':
        case 'J':
            req4CameraPitch -= REQ4_LOOK_STEP;

            if (req4CameraPitch < -REQ4_MAX_PITCH)
            {
                req4CameraPitch = -REQ4_MAX_PITCH;
            }
            break;

        case 'h':
        case 'H':
            req4CameraYaw -= REQ4_LOOK_STEP;
            break;

        case 'k':
        case 'K':
            req4CameraYaw += REQ4_LOOK_STEP;
            break;

        case 'l':
        case 'L':
            req4LightingEnabled = !req4LightingEnabled;
            break;

        case 'r':
        case 'R':
            angle = 0.0f;
            req1StarAngle = 0.0f;
            break;

        case 27: // Escape key
            std::exit(0);
            break;

        default:
            break;
    }
}



// wag idagdag 'to, pang reference comment lang

/*
    CS0045 - Technical Assessment 2
    Requirement 4: Keyboard, Camera, and Light Controls

    This file is meant to be appended to the provided starter program
    together with Req1-Star-Rotation-Translation.cpp.

    CONTROLS:

        W / S       Move forward / backward
        A / D       Move left / right
        Q / E       Move down / up on the Y-axis
        U / J       Look up / down
        H / K       Look left / right
        L           Toggle the star's light
        R           Reset the cube and star rotation angles
        Esc         End the program

    INTEGRATION STEPS:

    1. Add these prototypes with the starter program's other prototypes:

        void initializeReq4Lighting();
        void applyReq4Camera();
        void beginReq4StarLighting();
        void endReq4StarLighting();
        void handleReq4Keyboard(unsigned char key);

    2. Add this call at the end of initialize():

        initializeReq4Lighting();

    3. In display(), immediately after glMatrixMode(GL_MODELVIEW), add:

        applyReq4Camera();

       This replaces the camera matrix for the current frame.

    4. In display(), replace the Req1 drawReq1Star() call with:

        beginReq4StarLighting();
        drawReq1Star();
        endReq4StarLighting();

       This keeps lighting limited to the star. The cube remains unlit.

    5. In the starter program's keyboard() function, add:

        handleReq4Keyboard(key);
        glutPostRedisplay();
*/
