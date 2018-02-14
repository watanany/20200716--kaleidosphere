#include "Rect.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

Rect::Rect()
{
  init();
}

void Rect::init()
{
  // live
  m_live = true;
  // size
  m_size[0] = rand0_1() * 0.4 + 0.5;
  m_size[1] = rand0_1() * 0.4 + 0.5;
  // diffuse
  m_diffuse[0] = 1.0;
  m_diffuse[2] = 0.2;//rand0_1() * 0.20 + 0.70;
  m_diffuse[1] = rand0_1() * 0.30 + 0.25;
  m_diffuse[3] = rand0_1() * 0.50 + 0.40;

  // specular
  m_specular[0] = drand48() * 0.20 + 0.1;
  m_specular[1] = drand48() * 0.20 + 0.1;
  m_specular[2] = drand48() * 0.20 + 0.1;
  m_specular[3] = drand48() * 0.20 + 0.1;
  // shininess
  m_shininess = 30;
  // position
  m_pos[0] = -1.0 - (m_size[0]);
  m_pos[1] = rand0_1() * 3 - 1.5;
  // velocity
  m_v[0] = rand0_1() * 0.1;
  m_v[1] = rand0_1() * 0.1;
  // degree & spin velocity
  m_degree = randInt(0, 360);
  m_spin = rand0_1() * 90 - 45;
}

void Rect::draw()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);

  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPushMatrix();
  glTranslatef(m_pos[0], m_pos[1], 0.0);
  glRotatef(m_degree, 0.0, 0.0, 1.0);
  glScalef(m_size[0], m_size[1], 1.0);

  float a = rand0_1();
  if (a < 1.0/3.0) {
    glutSolidSphere(0.3, 32, 32);
  }
  else if (a < 2.0/3.0)  {
    glutSolidCube(0.7);
  }
  else {
    glutSolidTeapot(0.7);
  }

  glPopMatrix();
  glDisable(GL_BLEND);
  glDepthMask(GL_FALSE);
}

void Rect::move()
{
  if  (m_pos[0] >= (1.0+ m_size[0])) {
    m_live = false;
  }
  else {
    m_pos[0] += m_v[0];
    m_pos[1] += m_v[1];
    m_degree += m_spin;
  }

}

void Rect::revival()
{
  if (rand0_1() <= 0.15) {
    init();
  }
}

bool Rect::isAlive()
{
  return m_live;
}


float rand0_1(void)
{
  return (float)rand() / RAND_MAX;
}

int randInt(int begin, int end)
{
  int res;
  res = rand() % (end - begin + 1);
  res = res + begin;

  return res;
}


void drawKaleidTexture(Rect rects[], int size)
{
  for (int i = 0; i < size; i++) {
    if (rects[i].isAlive()) {
      rects[i].draw();
      rects[i].move();
    }
    else {
      rects[i].revival();
    }
  }
}
