#include "raylib.h"
#include <iostream>

const int window_width = 1200;
const int window_height = 600;
const char *window_title = "Dasher";

float delta = 0.0;
const float movement_positive_offset = 1.5;
const float movement_negative_offset = 1.0;

const float gravity = 9.8; // 9.8 m/s -> 0.8 -> acceleration due to gravity;

//
// Character
//

const float amount_sprites = 9.0;
const float animation_update_time = 1.0 / 12.0;

int animation_frame = 0;
float animation_running_time = 0.0;

// force = mass * acceleration;
int mass = 10;
int direction = 0;
float velocity = 0.0;

Vector2 character_position;
Texture2D character_texture;
Rectangle character_rectangle;

int get_floor_y() { return window_height - character_rectangle.height; }
int get_center_x() {
  return window_width / 2.0 - character_rectangle.width / 2;
}

int get_char_left_bound_x() { return character_position.x; }
int get_char_right_bound_x() {
  return character_position.x + character_rectangle.width;
}
int get_char_upper_bound_y() { return character_position.y; }
int get_char_lower_bound_y() {
  return character_position.y + character_rectangle.height;
}

bool is_floor() { return character_position.y >= get_floor_y(); }

//
// Hazard
//

Texture hazard_texture;

float print_debug = 0;
void debug_state() {
  print_debug += delta;

  if (print_debug < 0.5) {
    return;
  }

  std::cout << "DELTA: " << delta << std::endl;
  std::cout << "CHARACTER X: " << character_position.x << std::endl;
  std::cout << "CHARACTER Y: " << character_position.y << std::endl;
  std::cout << "GRAVITY: " << gravity << std::endl;
  std::cout << "VELOCITY: " << velocity << std::endl;
  std::cout << "FLOOR: " << is_floor() << std::endl;

  print_debug = 0;
}

void reset_movement() { velocity = 0.0; }
void apply_gravity() { velocity += gravity * delta; }
void check_boundaries() {
  if (is_floor()) {
    character_position.y = get_floor_y();
    velocity = 0;
  }
}

void controller() {
  debug_state();

  if (IsKeyPressed(KEY_SPACE) && is_floor()) {
    velocity -= 350.0 * delta;
  }

  apply_gravity();
  character_position.y += velocity;

  check_boundaries();
}

void character() {
  animation_running_time += delta;

  if (!is_floor()) {
    if (animation_running_time >= (animation_update_time * 2.5)) {
      animation_running_time = 0.0;
      animation_frame += 1;
    }
  } else {
    if (animation_running_time >= animation_update_time) {
      animation_running_time = 0.0;
      animation_frame += 1;
    }
  }

  if (animation_frame >= 9) {
    animation_frame = 0;
  }

  character_rectangle.x = character_rectangle.width * animation_frame;

  DrawTextureRec(character_texture, character_rectangle, character_position,
                 WHITE);
}

int main() {
  InitWindow(window_width, window_height, window_title);
  SetTargetFPS(60);

  // Load sprite
  character_texture = LoadTexture("./assets/character.png");
  hazard_texture = LoadTexture("./assets/hazard.png");

  character_rectangle.width = character_texture.width / amount_sprites;
  character_rectangle.height = character_texture.height;
  character_rectangle.x = 0;
  character_rectangle.y = 0;

  character_position.x = get_center_x();
  character_position.y = get_floor_y();

  while (true) {
    bool shouldCloseWindow =
        WindowShouldClose(); //&& !IsKeyPressed(KEY_ESCAPE);

    if (shouldCloseWindow) {
      debug_state();

      UnloadTexture(character_texture);
      UnloadTexture(hazard_texture);

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
