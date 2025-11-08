#include "raylib.h"

class Ground {
private:
  Texture2D ground = LoadTextureFromImage(LoadImage("assets/sprites/base.png"));
  // size: 336 x 112
  Vector2 pos = {0, 0};

public:
  Ground(float x, float y) {
    this->pos.x = x;
    this->pos.y = y;
  }

  void draw() { DrawTextureV(this->ground, this->pos, WHITE); };
  void update() {};

  Rectangle getHitBox() { return Rectangle{0, 400, 336, 112}; }
};