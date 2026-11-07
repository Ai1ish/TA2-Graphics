#include <cmath>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>
#include "star_lighting.h"

float req1StarAngle = 0.0f;
bool rotateObject = true;
GLuint VBOid = 0;

float req4CameraX = 0.0f;
float req4CameraY = 0.0f;
float req4CameraZ = 5.0f;

float req4CameraYaw = 0.0f;
float req4CameraPitch = 0.0f;

bool req4LightingEnabled = true;

const float REQ4_MOVE_STEP = 0.20f;
const float REQ4_LOOK_STEP = 3.0f;
const float REQ4_MAX_PITCH = 85.0f;
const float REQ4_DEGREES_TO_RADIANS = 0.0174532925f;

void initializeReq4Lighting()
{
  glShadeModel(GL_SMOOTH);
  setupStarLighting();
}
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
      0.0f);
}

void beginReq4StarLighting()
{
  if (req4LightingEnabled)
  {
    setupStarLighting();
  }
  else
  {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
  }
}

void endReq4StarLighting()
{
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void handleReq4Keyboard(unsigned char key)
{
  const float yawRadians =
      req4CameraYaw * REQ4_DEGREES_TO_RADIANS;

  const float forwardX = std::sin(yawRadians);
  const float forwardZ = -std::cos(yawRadians);

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
    req4CameraX += rightX * REQ4_MOVE_STEP;
    req4CameraZ += rightZ * REQ4_MOVE_STEP;
    break;

  case 'd':
  case 'D':
    req4CameraX -= rightX * REQ4_MOVE_STEP;
    req4CameraZ -= rightZ * REQ4_MOVE_STEP;
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

    req1StarAngle = 0.0f;
    break;

  case 27:
    std::exit(0);
    break;

  default:
    break;
  }
}

void drawReq1Star()
{
  glPushMatrix();
  glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(req1StarAngle, 0.0f, 1.0f, 0.0f);
  glColor3f(1.0f, 0.75f, 0.10f);
  drawStar(VBOid);
  glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  applyReq4Camera();
  beginReq4StarLighting();
  drawReq1Star();
  endReq4StarLighting();
  glutSwapBuffers();
}

void animate(int )
{
  if (rotateObject)
  {
    req1StarAngle += 1.0f;
    if (req1StarAngle >= 360.0f)
    {
      req1StarAngle -= 360.0f;
    }
  }
  glutPostRedisplay();
  glutTimerFunc(50, animate, 0);
}

void keyboard(unsigned char key, int , int )
{
  if (key == ' ')
  {
    rotateObject = !rotateObject;
  }
  handleReq4Keyboard(key);
  glutPostRedisplay();
}

void reshape(int width, int height)
{
  if (height < 1) height = 1;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, static_cast<double>(width) / height, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void initialize()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.025f, 0.035f, 0.065f, 1.0f);
  initializeStarVBO(VBOid);
  applyReq4Camera();
  setupStarLighting();
  initializeReq4Lighting();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("CS0045 - Rotating 3D Star");
  if (glewInit() != GLEW_OK)
  {
    return 1;
  }
  initialize();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(50, animate, 0);
  glutMainLoop();
  return 0;
}



