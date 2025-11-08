#include "raylib.h"
#include "vector"
#include <cstdlib>
#include <utility>

using namespace std;

struct Pipe {
  Vector2 pos;
  bool passed;
};

class Pipes {
private:
  Image pipe_img = LoadImage("assets/sprites/pipe-green.png"); // 52 x 320
  Texture2D pipe_up = LoadTextureFromImage(pipe_img);
  Texture2D pipe_down = LoadTextureFromImage(([&](Image arg) -> Image {
    Image tmp = ImageCopy(arg);
    ImageRotate(&tmp, 180);
    return tmp;
  })(pipe_img));
  vector<Pipe> pipes = {{{300, 10.f + rand() % 230}, false},
                        {{500, 10.f + rand() % 230}, false},
                        {{700, 10.f + rand() % 230}, false}};
  float speed = 75.;

public:
  pair<Vector2, Vector2> GapRect(float x, float y) {
    Vector2 up = {x, -320 + y};
    Vector2 down = {x, y + 80};
    return {up, down};
  }

  void draw() {
    for (const auto &pipe : this->pipes) {
      auto gap_pos = GapRect(pipe.pos.x, pipe.pos.y);
      DrawTextureV(this->pipe_down, gap_pos.first, WHITE);
      DrawTextureV(this->pipe_up, gap_pos.second, WHITE);
    }
  }

  void update() {
    for (int i = 0; i < 3; i++) {
      pipes[i].pos.x -= this->speed * GetFrameTime();

      if (pipes[i].pos.x <= -60) {
        pipes[i].pos.x = 600;
        pipes[i].pos.y = 10 + rand() % 230;
        pipes[i].passed = false;
      }
    }
  }

  vector<pair<Rectangle, Rectangle>> GetHitboxes() {
    vector<pair<Rectangle, Rectangle>> res;
    for (const auto &pipe : this->pipes) {
      auto gap_pos = GapRect(pipe.pos.x, pipe.pos.y);
      res.push_back(make_pair(
          Rectangle{gap_pos.first.x + 3, gap_pos.first.y + 3, 46, 320},
          Rectangle{gap_pos.second.x + 3, gap_pos.second.y + 3, 46, 320}));
    }
    return res;
  }

  void reinitializePipes() {
    this->pipes = {{{300, 10.f + rand() % 230}, false},
                   {{500, 10.f + rand() % 230}, false},
                   {{700, 10.f + rand() % 230}, false}};
  }

  Pipe getPipeInfo(int id) { return this->pipes[id]; }

  void setPassed(int id, bool val) { this->pipes[id].passed = val; }
};