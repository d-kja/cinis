#include "raylib.h"
#include <cstdio>
#include <iostream>

const int window_width = 1200;
const int window_height = 600;
const char *window_title = "Dasher";

float delta = 0.0;
int velocity = 0;
const float movement_positive_offset = 1.5;
const float movement_negative_offset = 1.0;

//
// Character
//

const int char_height = 40;
const int char_width = 25;

int get_floor_y() { return window_height - char_height; }
int get_center_x() { return window_width / 2.0; }

float char_x = get_center_x();
float char_y = get_floor_y();

int movement_y = 0;
int movement_x = 0;

int get_char_left_bound_x() { return char_x; }
int get_char_right_bound_x() { return char_x + char_width; }
int get_char_upper_bound_y() { return char_y; }
int get_char_lower_bound_y() { return char_y + char_height; }

void debug_state() {
  std::cout << "Delta: " << delta << std::endl;
  std::cout << "Velocity: " << velocity << std::endl;
  std::cout << "Movement X: " << movement_x << std::endl;
  std::cout << "Movement Y: " << movement_y << std::endl;
  std::cout << "Character X: " << char_x << std::endl;
  std::cout << "Character Y: " << char_y << std::endl;
}

void reset_movement() {
  movement_x = 0;
  movement_y = 0;

  velocity = 0;
}

void controller() {
  bool is_jumping = movement_y == 1;
  bool is_floor = char_y == get_floor_y();
  bool should_fall =
      char_y < get_floor_y(); // scuffed, doesn't work with platform

  if (IsKeyPressed(KEY_D)) {
    if (is_jumping || should_fall) {
      movement_x = -1;
      return;
    }

    velocity = 500;
    movement_x = -1;
  }

  if (IsKeyPressed(KEY_A)) {
    if (is_jumping || should_fall) {
      movement_x = 1;
      return;
    }

    velocity = 500;
    movement_x = 1;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    if (is_jumping) {
      return;
    }

    velocity = 500;
    movement_y = 1;
  }

  // Handle movement
  if (velocity < 0) {
    velocity += 15;

    if (velocity > 0) {
      velocity = 0;
    }
  }

  if (velocity > 0) {
    if (should_fall && movement_y < 0) {
      velocity += 30;
    } else {
      velocity -= 15;
    }

    if (is_floor && movement_y < 0) {
      velocity = 0;
    }

    if (velocity < 0) {
      velocity = 0;
    }
  }

  bool reset_velocity = velocity == 0;
  if (reset_velocity) {
    reset_movement();
  }

  if (should_fall && reset_velocity) {
    velocity = 200;
    movement_y = -1;
  }

  if (movement_x < 0) {
    float movement_offset = velocity * delta;
    std::cout << "Offset: " << movement_offset << std::endl;
    std::cout << "Current: " << char_x << std::endl;

    char_x += movement_offset;

    std::cout << "Updated: " << char_x << std::endl;
  }
  if (movement_x > 0) {
    float movement_offset = velocity * delta;
    std::cout << "Offset: " << movement_offset << std::endl;
    std::cout << "Current: " << char_x << std::endl;

    char_x -= movement_offset;

    std::cout << "Updated: " << char_x << std::endl;
  }

  if (movement_y < 0) {
    float movement_offset = velocity * delta;
    char_y += movement_offset;

    if (char_y > get_floor_y()) {
      char_y = get_floor_y();
    }
  }
  if (movement_y > 0) {
    float movement_offset = velocity * delta;
    char_y -= movement_offset;
  }

  debug_state();
}

void character() {
  DrawRectangle(char_x, char_y, char_width, char_height, RED);
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
