#include "enemy.h"
#include "static.h"

#include <raylib.h>

Enemy::Enemy(Texture2D running_texture, Texture2D idle_texture,
             Vector2 position)
    : texture_running(running_texture), texture_idle(idle_texture),
      texture(idle_texture) {
  float sprite_width = this->texture.width / ENEMY_AMOUNT_SPRITES;
  float sprite_height = this->texture.height;

  float scaled_width = sprite_width * BASE_SCALE;
  float scaled_height = sprite_height * BASE_SCALE;

  this->window_position = {.x = position.x,
                           .y = position.y,
                           .width = scaled_width,
                           .height = scaled_height};
}

void Enemy::render_enemy() {
  this->update_position();

  DrawTexturePro(this->texture, this->sprite_position, this->window_position,
                 {0.f, 0.f}, this->rotation, RAYWHITE);
}

void Enemy::update_position() {
  float sprite_width = this->texture.width / ENEMY_AMOUNT_SPRITES;
  float sprite_height = this->texture.height;

  float sprite_direction = this->direction.x < 0.f ? 1.f : -1.f;
  this->sprite_position = {.x = sprite_width * this->animation_frame,
                           .y = 0.0f,
                           .width = sprite_direction * sprite_width,
                           .height = sprite_height};

  float scaled_width = sprite_width * BASE_SCALE;
  float scaled_height = sprite_height * BASE_SCALE;

  this->window_position = {.x = this->window_position.x,
                           .y = this->window_position.y,
                           .width = scaled_width,
                           .height = scaled_height};
}

void Enemy::update_delta(float delta) {
  this->delta = delta;
  this->animation_time += delta;

  if (this->animation_time > ANIMATION_TIME_BASE) {
    this->animation_time = 0.0;
    this->animation_frame++;
  }

  bool reset = this->animation_time > ANIMATION_TIME_BASE;

  if (this->animation_frame > ENEMY_AMOUNT_SPRITES) {
    this->animation_frame = 0.0;
  }
}

void Enemy::clean_up() {
  UnloadTexture(this->texture_idle);
  UnloadTexture(this->texture_running);
}
