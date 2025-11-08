#include "raylib.h"
#include <utility>
#include <vector>

using namespace std;

class Score {
private:
  int scoreNumber = 0;
  vector<int> scoreDigits;
  vector<pair<Texture2D, float>> imgs;
  vector<Texture2D> digitsTexture = {
      LoadTextureFromImage(LoadImage("assets/sprites/0.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/1.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/2.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/3.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/4.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/5.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/6.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/7.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/8.png")),
      LoadTextureFromImage(LoadImage("assets/sprites/9.png")),
  };
  Sound scoreSFX = LoadSound("assets/audio/point.wav");

  int getTotalWidth() {
    int sum = 0;
    for (const auto &x : scoreDigits) {
      sum += x == 1 ? 16 : 24;
    }
    return sum;
  }

  void getTextureArray(int startX = 0) {
    vector<pair<Texture2D, float>> tmp;

    for (int i = this->scoreDigits.size() - 1; i >= 0; --i) {
      Texture2D digitImg = digitsTexture[this->scoreDigits[i]];
      tmp.push_back(make_pair(digitImg, tmp.empty()
                                            ? startX
                                            : tmp[tmp.size() - 1].first.width +
                                                  tmp[tmp.size() - 1].second));
    }
    this->imgs = tmp;
  }

public:
  Score(int score) { this->setScore(score); }

  void setScore(int score) {
    this->scoreNumber = score;
    this->scoreDigits.clear();
    if (score == 0) {
      this->scoreDigits = {0};
    } else {
      while (score != 0) {
        this->scoreDigits.push_back(score % 10);
        score /= 10;
      }
    }
  }

  int getScore() { return this->scoreNumber; }

  void draw() {
    getTextureArray(144 - getTotalWidth() / 2);
    for (const auto &digit : imgs) {
      DrawTextureV(digit.first, Vector2{digit.second, 36}, WHITE);
    }
  }

  void playSFX() { PlaySound(this->scoreSFX); }
};