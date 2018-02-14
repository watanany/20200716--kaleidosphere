#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

class Framebuffer {
 protected:
  int rbWidth;
  int rbHeight;
  GLuint fbID;
  GLuint rbID;
  GLuint texID;

  void initTexture();
  void initRenderbuffer();
  void initFramebuffer();

 public:

  Framebuffer();
  ~Framebuffer();

  void init(int width, int height);

  void draw(void (*drawFunc)(void));


  int width() {
    return rbWidth;
  }

  int height() {
    return rbHeight;
  }

  GLuint getFramebufferID() {
    return fbID;
  }

  GLuint getRenderbufferID() {
    return rbID;
  }

  GLuint getTextureID() {
    return texID;
  }
};
