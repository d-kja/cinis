#include "enemies.h"
#include <raylib.h>

#include "enemy.h"

void Enemies::setup() {
  Texture2D enemy_idle = LoadTexture("assets/goblin_idle.png");
  Texture2D enemy_running = LoadTexture("assets/goblin-run.png");

  Vector2 position_01{.x = 0.f, .y = 0.f};
  Enemy enemy_01{enemy_running, enemy_idle, position_01};

  this->enemies.push_back(enemy_01);
}

void Enemies::render() {
  for (auto &enemy : enemies) {
    enemy.render_enemy();
  }
}

void Enemies::clean_up() {
  for (auto &enemy : enemies) {
    enemy.clean_up();
  }
}

void Enemies::update_delta(float delta) {
  for (auto &enemy : enemies) {
    enemy.update_delta(delta);
  }
}
