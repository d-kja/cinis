#include "raylib.h"
#include <cstdio>
#include <iostream>

const int window_width = 1200;
const int window_height = 600;
const char *window_title = "Dasher";

float delta = 0.0;
const float movement_positive_offset = 1.5;
const float movement_negative_offset = 1.0;

// force = mass * acceleration;
float acceleration = 10;
const float gravity = 9.8; // 9.8 m/s -> 0.8 -> acceleration due to gravity;

//
// Character
//

int mass = 10;
float velocity = 0.0;

const int char_height = 40;
const int char_width = 25;

int get_floor_y() { return window_height - char_height; }
int get_center_x() { return window_width / 2.0; }

float character_x = get_center_x();
float character_y = get_floor_y();

int get_char_left_bound_x() { return character_x; }
int get_char_right_bound_x() { return character_x + char_width; }
int get_char_upper_bound_y() { return character_y; }
int get_char_lower_bound_y() { return character_y + char_height; }

bool is_floor() { return character_y >= get_floor_y(); }

float print_debug = 0;
void debug_state() {
  print_debug += delta;

  if (print_debug < 0.5) {
    return;
  }

  std::cout << "DELTA: " << delta << std::endl;
  std::cout << "CHARACTER X: " << character_x << std::endl;
  std::cout << "CHARACTER Y: " << character_y << std::endl;
  std::cout << "GRAVITY: " << gravity << std::endl;
  std::cout << "VELOCITY: " << velocity << std::endl;
  std::cout << "FLOOR: " << is_floor() << std::endl;

  print_debug = 0;
}

void reset_movement() { velocity = 0.0; }
void apply_gravity() { velocity += gravity * delta; }
void check_boundaries() {
  if (is_floor()) {
    character_y = get_floor_y();
    velocity = 0;
  }
}

void controller() {
  debug_state();

  if (IsKeyPressed(KEY_SPACE) && is_floor()) {
    velocity -= 350.0 * delta;
  }

  apply_gravity();
  character_y += velocity;

  check_boundaries();
}

void character() {
  DrawRectangle(character_x, character_y, char_width, char_height, RED);
}

int main() {
  InitWindow(window_width, window_height, window_title);
  SetTargetFPS(60);

  while (true) {
    bool shouldCloseWindow =
        WindowShouldClose(); //&& !IsKeyPressed(KEY_ESCAPE);

    if (shouldCloseWindow) {
      debug_state();
      CloseWindow();
      return 0;
    }

    BeginDrawing();
    ClearBackground(WHITE);

    delta = GetFrameTime();

    character();
    controller();

    EndDrawing();
  }
}
