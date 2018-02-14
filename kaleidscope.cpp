#include "kaleidscope.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowSize(width, height);
  glutCreateWindow("Kaleid Sphere");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMouseFunc(mouse);

  init();

  glutMainLoop();

  return EXIT_SUCCESS;
}


void display()
{
  if (stop) { return; }

  initLight();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  reshape(width, height);
  framebuffer.draw(drawKaleidTexture_);
  if (mode == 0) {
    drawKaleidTexture_();
  }

  if (mode == 1 || mode == 2) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    reshape(width, height);
    framebuffer.draw(drawKaleidScope);
    if (mode == 1) {
      drawKaleidScope();
    }
    if (mode == 2) {
      const float pos1[] = {
  -5.0, -5.0, 0.0
      };

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      reshape(width, height);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(eye[0], eye[1], eye[2],
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.0);
      glLightfv(GL_LIGHT1, GL_POSITION, pos1);


      GLfloat d[] = {0.70, 0.0, 0.40};
      GLfloat s[] = {0.80, 0.0, 0.0};
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
      glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15);

      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, framebuffer.getTextureID());
      glPushMatrix();
#if 0
      gluSphere(sphere, 1.0, 256, 256);
#else
      glEnable(GL_TEXTURE_GEN_S);
      glEnable(GL_TEXTURE_GEN_T);
      glutSolidSphere(1.0, 1024, 1024);
      glDisable(GL_TEXTURE_GEN_S);
      glDisable(GL_TEXTURE_GEN_T);
      glutWireSphere(1.0, 32, 32);
#endif
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }
  }


  glutSwapBuffers();
}


void reshape(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 0.5,
      0.0, 0.0, 0.0,
      0.0, 1.0, 0.0);
}



void keyboard(unsigned char key, int x, int y)
{
  static const float amount = 0.04;
  static const float eye_ini[] = {
    eye[0], eye[1], eye[2]
  };


  if (isalnum(key)) {
    printf("key: %c\n", key);
  }
  else {
    printf("key: %d\n", key);
  }

  switch (key) {
  case 27:
  case 'q':
    glutDestroyWindow(glutGetWindow());
    exit(EXIT_SUCCESS);
    break;
  case 'i':
    eye[0] = eye_ini[0];
    eye[1] = eye_ini[1];
    eye[2] = eye_ini[2];
    break;
  case 13:    // Press ENTER
    stop = !stop;
    break;
  case 32:    // Press SPACE
    mode = (mode + 1) % 3;
    break;
  case 'x':
  case 'y':
  case 'z':
    eye[key - 'x'] += amount;
    break;
  case 'X':
  case 'Y':
  case 'Z':
    eye[key - 'X'] -= amount;
    break;
  default:
    break;
  }
}

void idle()
{
  static int FPS = 60;

  clock_t start = clock();
  while (1) {
    clock_t end = clock();
    if ((double)(end - start)/CLOCKS_PER_SEC >= 1.0/FPS) break;
  }

  glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{

}



void drawKaleidTexture_()
{
  glPushMatrix();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  reshape(texWidth, texHeight);

  glPushMatrix();
  drawKaleidTexture(rects, MAX_RECT);
  glPopMatrix();
}




void drawKaleidScope()
{
  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, framebuffer.getTextureID());

  const float ROOT_3 = sqrt(3);
  bool initTopSideFlag = false;
  for (float y = -1.0; y <= 1.0 + EDGE_LENGTH; y += EDGE_LENGTH / 2 * ROOT_3) {
    bool topSideFlag = initTopSideFlag;
    int texturePointIndex = 0;

    glBegin(GL_TRIANGLE_STRIP);
    for (float x = -1.0 - EDGE_LENGTH; x <= 1.0 + EDGE_LENGTH; x += EDGE_LENGTH / 2) {
      float pointY = topSideFlag ? y : y + EDGE_LENGTH / 2 * ROOT_3;

      glTexCoord2f(TEXTURE_POINT_X[texturePointIndex],
       TEXTURE_POINT_Y[texturePointIndex]);
      glVertex3f(x, pointY, 0.0);

      topSideFlag = !topSideFlag;
      texturePointIndex = (texturePointIndex + 1) % 3;
    }
    glEnd();
    initTopSideFlag = !initTopSideFlag;
  }

  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  glPopMatrix();
}



void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);

  srand((unsigned)time(NULL));
  srand48((unsigned)time(NULL));

  initLight();
  glEnable(GL_DEPTH_TEST);

  if (glewInit() != GLEW_OK) {
    exit(EXIT_FAILURE);
  }
  framebuffer.init(texWidth, texHeight);

  sphere = gluNewQuadric();
  gluQuadricDrawStyle(sphere, GLU_FILL);
  gluQuadricNormals(sphere, GLU_SMOOTH);
  gluQuadricTexture(sphere, GL_TRUE);
}



void initLight()
{
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

  /* set light position, diffuse, and eznable lights */
  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

  glLightfv(GL_LIGHT1, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light0_specular);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
}

