#include "background.h"
#include "static.h"
#include <array>


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

void Background::render_background(float char_width, float char_height) {
  this->handle_boundary();

  DrawTextureEx(this->texture, this->position, this->rotation, this->scale,
                RAYWHITE);
}

void Background::handle_boundary() {
  std::array<float, 2> center = this->get_background_center_offset();
  std::array<float, 2> size = this->get_background_size();

  float smol_offset = 25.0;

  float background_x = 0.f;
  float background_y = this->position.y;

  float right_bound = center[0] - size[0] / 2.0 + smol_offset * 2.0;
  float left_bound = center[0] + size[0] / 2.0 - smol_offset * 2.0;

  float bottom_bound = center[1] - size[1] / 2.0 + smol_offset * 6.0;
  float top_bound = center[1] + size[1] / 2.0 - smol_offset;

  if (left_bound < this->position.x) {
    this->position = this->last_position;
  }

  if (right_bound > this->position.x) {
    this->position = this->last_position;
  }

  if (top_bound < this->position.y) {
    this->position = this->last_position;
  }

  if (bottom_bound > this->position.y) {
    this->position = this->last_position;
  }
}

void Backgrounds::setup_backgrounds() {
  this->primary.setup_background("assets/map.png");
}
void Backgrounds::clean_up_backgrounds() {
  this->primary.clean_up_background();
}
void Backgrounds::render_backgrounds(float char_width, float char_height) {
  this->primary.render_background(char_width, char_height);
}
