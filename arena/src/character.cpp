#include "character.h"
#include "background.h"
#include "static.h"

#include <raylib.h>
#include <raymath.h>

Character::Character(_Window window) {
  this->window = window;
};

void Character::handle_controller(Backgrounds *backgrounds) {
  this->direction = {};
  this->texture = this->texture_idle;

  if (IsKeyDown(KEY_A))
    direction.x += 1.0;
  if (IsKeyDown(KEY_D))
    direction.x -= 1.0;
  if (IsKeyDown(KEY_W))
    direction.y += 1.0;
  if (IsKeyDown(KEY_S))
    direction.y -= 1.0;

  if (IsKeyDown(KEY_LEFT_SHIFT)) {
    this->speed = 1.25;
  } else {
    this->speed = 0.75;
  }

  bool should_move = Vector2Length(direction) != 0.0;
  if (should_move) {
    this->texture = this->texture_running;

    float scalar = this->speed * BASE_SPEED * this->delta;
    Vector2 normalized_value =
        Vector2Scale(Vector2Normalize(direction), scalar);
    Vector2 new_position =
        Vector2Add(backgrounds->primary.position, normalized_value);

    backgrounds->primary.last_position = backgrounds->primary.position;
    backgrounds->primary.position = new_position;
  }
}

void Character::update_position() {
  float sprite_width = this->texture.width / this->sprites;
  float sprite_height = this->texture.height;

  float window_width = *this->window.width;
  float window_height = *this->window.height;

  float sprite_direction = this->direction.x < 0.0 ? 1.0 : -1.0;
  this->sprite_position = {
    .x = sprite_width * this->animation_frame,
    .y = 0.0f,
    .width = sprite_direction * sprite_width,
    .height = sprite_height
  };

  float scaled_width = sprite_width * BASE_SCALE;
  float scaled_height = sprite_height * BASE_SCALE;

  float position_x = (window_width / 2.0) - (scaled_width / 2.0);
  float position_y = (window_height / 2.0) - (scaled_height / 2.0);

  this->window_position = {
      .x = position_x,
      .y = position_y,
      .width = scaled_width,
      .height = scaled_height,
  };
}

void Character::render_character() {
  this->update_position();

  DrawTexturePro(this->texture, this->sprite_position, this->window_position,
                 this->position, 0, RAYWHITE);
}

void Character::update_delta(float delta) {
  this->delta = delta;
  this->animation_time += delta;

  if (this->animation_time > ANIMATION_TIME_BASE) {
    this->animation_time = 0.0;
    this->animation_frame++;
  }

  if (this->animation_frame > AMOUNT_SPRITES) {
    this->animation_frame = 0.0;
  }
}

void Character::setup() {
  this->texture_idle = LoadTexture("assets/char_idle.png");
  this->texture_running = LoadTexture("assets/char_running.png");

  // Default texture
  this->texture = this->texture_idle;
}

void Character::clean_up() {
  UnloadTexture(texture_idle);
  UnloadTexture(texture_running);
}
