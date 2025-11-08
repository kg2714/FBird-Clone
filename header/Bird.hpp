#include "raylib.h"
#include "vector"
#include <algorithm>
using namespace std;

class Bird {
private:
  vector<Texture2D> animation = {
      LoadTextureFromImage(LoadImage("assets/sprites/yellowbird-upflap.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/yellowbird-midflap.png")),
      LoadTextureFromImage(
          LoadImage("assets/sprites/yellowbird-downflap.png"))}; // 34 x 24
  int current_idx = 0;
  double speed = 0.35, interval = 0;
  double velocity = 100, acceleration = 275;
  Vector2 pos = {0, 0};

  Sound flapSound = LoadSound("assets/audio/wing.wav");

public:
  Bird(float x, float y) {
    this->pos.x = x;
    this->pos.y = y;
  }
 
  void draw() {
    DrawTextureV(this->animation[this->current_idx], this->pos, WHITE);
  }

  void update_move() {
    this->pos.y =
        clamp(this->pos.y + this->velocity * GetFrameTime(), -30., 376.);
    this->velocity = this->velocity + this->acceleration * GetFrameTime();
  }

  void animate() {
    this->interval -= GetFrameTime();
    if (this->interval <= 0.) {
      this->interval = this->speed;
      this->current_idx = (this->current_idx + 1) % 3;
    }
  }

  void flapEvent() {
    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      this->velocity = -125;
      PlaySound(this->flapSound);
    }
  }

  void update_gameOver() { current_idx = 1; }

  Vector2 getPos() { return this->pos; }

  void resetState() {
    this->pos = Vector2{50, 185};
    this->velocity = 100;
  }

  Rectangle getHitBox() { return Rectangle{this->pos.x+3, this->pos.y+2, 28, 18}; }
};