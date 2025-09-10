#include "./background.h"
#include <array>
#include <iostream>

float BASE_SCALE = 4.0;

std::array<float, 2> Background::get_background_size() {
  float x_axis = this->texture.width * BASE_SCALE;
  float y_axis = this->texture.height * BASE_SCALE;

  std::array<float, 2> arr = {x_axis, y_axis};
  return arr;
}

std::array<float, 2> Background::get_background_center_offset() {
  float width = GetRenderWidth() / 2.0;
  float height = GetRenderHeight() / 2.0;

  std::array<float, 2> axis = this->get_background_size();

  // WINDOW OFFSET WITH CURRENT TEXTURE
  float offset_x = (width - axis[0] / 2.0);
  float offset_y = (height - axis[1] / 2.0);

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
  std::array<float, 2> background_size = this->get_background_size();
  std::array<float, 2> background_offset = this->get_background_center_offset();

  float background_width = background_size[0];
  float background_height = background_size[1];

  float background_offset_x = background_offset[0] * 2.0;
  float background_offset_y = background_offset[1] * 2.0;

  float left_bound = background_width / 2.0 + background_offset_x;
  float right_bound =(background_width / 2.0 * -1.0) + background_offset_x;

  std::cout << "POS X: " << this->position.x << std::endl;
  std::cout << "POS Y: " << this->position.y << std::endl;
  std::cout << "LEFT BOUND OFFSET X: " << background_offset_x << std::endl;
  std::cout << "LEFT BOUND OFFSET Y: " << background_offset_y << std::endl;
  std::cout << "LEFT BOUND X: " << left_bound << std::endl;
  std::cout << "RIGHT BOUND X: " << right_bound << std::endl;

  if (left_bound < this->position.x) {
    this->position = this->last_position;
  }

  if (right_bound > this->position.x) {
    this->position = this->last_position;
  }

  DrawTextureEx(this->texture, this->position, this->rotation, this->scale,
                RAYWHITE);
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
