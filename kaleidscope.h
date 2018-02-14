#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include "Rect.h"
#include "Framebuffer.h"

void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle();
void mouse(int button, int state, int x, int y);
void drawKaleidTexture_();
void drawKaleidScope();
void init();
void initLight();

#define EDGE_LENGTH 0.75
#define MAX_RECT 100

Rect rects[MAX_RECT];

Framebuffer framebuffer;

GLUquadricObj* sphere;

int width = 512;
int height = 512;
int texWidth = 512;
int texHeight = 512;
bool stop = false;
int mode = 2;

const float TEXTURE_POINT_X[] = {1, 0.5, 0};
const float TEXTURE_POINT_Y[] = {1, 0, 1};

GLfloat eye[3] = {0.0, 0.0, 1.8};


const GLfloat globalAmbient[] = {0.1, 0.1, 0.1, 1.0};
const GLfloat light0_pos[] = {3.0, 3.0, 3.0, 1.0};
const GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
const GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0};
const GLfloat light1_pos[] = {-4.0, -4.0, 3.0, 1.0};
const GLfloat light1_diffuse[] = {0.3, 0.3, 0.3, 1.0};
