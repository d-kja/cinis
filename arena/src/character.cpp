#include "character.h"
#include "background.h"

#include <raylib.h>
#include <raymath.h>

const float BASE_SPEED = 500.0;
const float AMOUNT_SPRITES = 6.0;
const float ANIMATION_TIME_BASE = 1.0 / 12.0;

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
  float window_width_center = *this->window.width / 2.0;
  float window_height_center = *this->window.height / 2.0;

  float character_width_center = BASE_SCALE * this->texture.width / 2.0;
  float character_height_center = BASE_SCALE * this->texture.height / 2.0;

  float x = window_width_center - character_width_center;
  float y = window_height_center - character_height_center;

  float sprite_width = this->texture.width / this->sprites;
  float sprite_height = this->texture.height;

  float sprite_direction = this->direction.x < 0.0 ? 1.0 : -1.0;
  this->sprite_position = {.x = sprite_width * this->animation_frame,
                           .y = 0.0f,
                           .width = sprite_direction * sprite_width,
                           .height = sprite_height};

  this->window_position = {
      .x = x,
      .y = y,
      .width = sprite_width * BASE_SCALE,
      .height = sprite_height * BASE_SCALE,
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
