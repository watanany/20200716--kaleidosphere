#include "Framebuffer.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Framebuffer::Framebuffer()
{
  rbWidth = 0;
  rbHeight = 0;
  fbID = 0;
  rbID = 0;
  texID = 0;
}

Framebuffer::~Framebuffer()
{
  glDeleteFramebuffersEXT(1, &fbID);
  glDeleteRenderbuffersEXT(1, &rbID);
  glDeleteTextures(1, &texID);

  fbID = rbID = texID = 0;
}

void Framebuffer::init(int width, int height)
{
  rbWidth = width;
  rbHeight = height;

  if (!GLEW_EXT_framebuffer_object) {
    cerr << "Error : フレームバッファオブジェクトがサポートされていません\n" << endl;
    exit(EXIT_SUCCESS);
  }

  initTexture();
  initRenderbuffer();
  initFramebuffer();
}

void Framebuffer::draw(void (*drawFunc)(void))
{
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);
  drawFunc();
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}



void Framebuffer::initTexture()
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_2D, texID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rbWidth, rbHeight,
         0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

void Framebuffer::initRenderbuffer()
{
  glGenRenderbuffersEXT(1, &rbID);
  glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rbID);
  glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT,
         rbWidth, rbHeight);
}

void Framebuffer::initFramebuffer()
{
  glGenFramebuffersEXT(1, &fbID);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);

  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
          GL_TEXTURE_2D, texID, 0);
  glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
             GL_RENDERBUFFER_EXT, rbID);

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
