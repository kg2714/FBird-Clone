#include "header/Bird.hpp"
#include "header/Ground.hpp"
#include "header/Pipes.hpp"
#include "header/ScoreManager.hpp"
#include <cstdlib>
#include <ctime>
#include <raylib.h>

using namespace std;

#define SCREEN_WIDTH 288
#define SCREEN_HEIGHT 512

int main() {
  srand(time(nullptr));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
  InitAudioDevice();
  SetMasterVolume(0.75f);
  Image icon = LoadImage("./assets/game_icon.png");
  SetWindowIcon(icon);
  SetTargetFPS(360);

  Image welcomeScreen = LoadImage("assets/sprites/message.png");
  Texture splash = LoadTextureFromImage(welcomeScreen);
  Vector2 message_pos = {(SCREEN_WIDTH * 1.f - welcomeScreen.width) / 2,
                         (SCREEN_HEIGHT * 1.f - welcomeScreen.height) / 2};
  bool playing = false;

  Texture2D bg =
      LoadTextureFromImage(LoadImage("./assets/sprites/background-day.png"));

  Bird bird(50, 185);
  Ground ground(0, 400);
  Pipes pipes;

  bool gameOver;
  Image gameOverScreen = LoadImage("assets/sprites/gameover.png");
  Texture2D over = LoadTextureFromImage(gameOverScreen);
  Vector2 gameOver_pos = {(SCREEN_WIDTH * 1.f - gameOverScreen.width) / 2,
                          (SCREEN_HEIGHT * 1.f - gameOverScreen.height) / 2};

  pair<Sound, bool> hit = {LoadSound("assets/audio/hit.wav"), false};

  bool toggleFPS = false;

  Score score(0);
  auto restartGame = [&]() -> void {
    bird.resetState();
    pipes.reinitializePipes();
    gameOver = false;
    hit.second = false;
    playing = false;
    score.setScore(0);
  };

  bool scored_pipes[3] = {false, false, false};

  while (!WindowShouldClose()) {
    BeginDrawing();

    // Draw
    ClearBackground(WHITE);

    DrawTexture(bg, 0, 0, WHITE);
    if (IsKeyPressed(KEY_R)) {
      restartGame();
    }

    pipes.draw();
    bird.draw();
    ground.draw();

    // Update
    if (playing) {
      bird.animate();
      pipes.update();
      bird.flapEvent();

      bird.update_move();

      for (int i = 0; i < 3; i++) {
        if (pipes.getPipeInfo(i).pos.x <= 16 &&
            (!pipes.getPipeInfo(i).passed)) {
          score.playSFX();
          score.setScore(score.getScore() + 1);
          pipes.setPassed(i, true);
        }
      }

      Rectangle birdHitbox = bird.getHitBox();

      for (auto &box : pipes.GetHitboxes()) {
        if (CheckCollisionRecs(box.first, birdHitbox) ||
            CheckCollisionRecs(box.second, birdHitbox) ||
            bird.getPos().y >= 376.) {
          gameOver = true;
          playing = false;
          break;
        }
      }

    } else {
      if (gameOver) {
        bird.update_move();
        bird.update_gameOver();
        if (!hit.second) {
          PlaySound(hit.first);
          hit.second = true;
        }
        DrawTextureV(over, gameOver_pos, WHITE);
        if (IsKeyPressed(KEY_R) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
          restartGame();
        }
      } else {
        DrawTextureV(splash, message_pos, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
            IsKeyPressed(KEY_SPACE)) {
          playing = true;
        }
        bird.animate();
      }
    }
    score.draw();
    if (toggleFPS) {
      DrawFPS(20, 20); // benchmark
    }

    if (IsKeyPressed(KEY_F)) {
      toggleFPS = !toggleFPS;
    }

    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();
  return 0;
}