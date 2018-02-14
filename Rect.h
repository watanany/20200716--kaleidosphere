#pragma once

class Rect {
  float m_pos[2];
  float m_v[2];
  float m_size[2];
  float m_diffuse[4];
  float m_specular[4];
  float m_shininess;
  float m_degree;
  float m_spin;
  bool m_live;

 public:
  Rect();
  void init();
  void draw();
  void move();
  void revival();
  bool isAlive();
};

float rand0_1();
int randInt(int begin, int end);

void drawKaleidTexture(Rect rects[], int size);
