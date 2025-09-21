#include "background.h"
#include "static.h"
#include <array>
#include <raylib.h>
#include <raymath.h>

std::array<float, 2> Background::get_background_size() {
  float x_axis = this->texture.width * BASE_SCALE;
  float y_axis = this->texture.height * BASE_SCALE;

  std::array<float, 2> arr = {x_axis, y_axis};
  return arr;
}

std::array<float, 2> Background::get_background_center_offset() {
  std::array<float, 2> axis = this->get_background_size();

  float width = GetRenderWidth() / 2.0;
  float height = GetRenderHeight() / 2.0;

  float axis_x_offset = axis[0] / 2.0;
  float axis_y_offset = axis[1] / 2.0;

  float offset_x = (width - axis_x_offset);
  float offset_y = (height - axis_y_offset);

  std::array<float, 2> offsets{offset_x, offset_y};

  return offsets;
}

void Background::clean_up_background() { UnloadTexture(this->texture); }
void Background::setup_background(const char *path) {
  this->texture = LoadTexture(path);

  std::array<float, 2> center = this->get_background_center_offset();

  this->position.x = center[0];
  this->position.y = center[1];

  this->scale = BASE_SCALE;
}

void Background::render_background() {
  DrawTextureEx(this->texture, this->position, this->rotation, this->scale,
                RAYWHITE);
}

std::array<Vector2, 2> Background::get_center(Vector2 character_position) {
  Vector2 origin = Vector2Subtract(
      this->position, character_position); // Straight the fuck up  better to
                                           // calculate boundaries

  float background_width = this->texture.width * this->scale;
  float background_height = this->texture.height * this->scale;

  float window_width = (float)GetRenderWidth();
  float window_height = (float)GetRenderHeight();

  float half_window_width = window_width / 2.f;
  float half_window_height = window_height / 2.f;

  std::array<float, 2> background_x{origin.x - half_window_width,
                                    origin.x - half_window_width +
                                        background_width};
  std::array<float, 2> background_y{origin.y - half_window_height,
                                    origin.y - half_window_height +
                                        background_height};

  std::array<Vector2, 2> center = {
      Vector2{.x = background_x[0], .y = background_y[0]},
      Vector2{.x = background_x[1], .y = background_y[1]},
  };

  return center;
}

void Background::handle_collision(Vector2 character_position) {
  std::array<Vector2, 2> background_position =
      this->get_center(character_position);

  float left_bound = background_position[0].x + 50.f;
  float right_bound = background_position[1].x - 50.f;

  float top_bound = background_position[0].y + 30.f;
  float bottom_bound = background_position[1].y - 150.f;

  if (left_bound >= 0.f) {
    this->revert_step();
  }

  if (right_bound <= 0.f) {
    this->revert_step();
  }

  if (top_bound >= 0.f) {
    this->revert_step();
  }

  if (bottom_bound <= 0.f) {
    this->revert_step();
  }
}

void Background::revert_step() { this->position = this->last_position; }

void Backgrounds::setup_backgrounds() {
  this->primary.setup_background("assets/map.png");
}

void Backgrounds::clean_up_backgrounds() {
  this->primary.clean_up_background();
}

void Backgrounds::render_backgrounds() { this->primary.render_background(); }
