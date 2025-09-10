#include "./background.h"

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
  float offset_x = (width - axis[0]);
  float offset_y = (height - axis[1]);

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
  float width = GetRenderWidth() / 2.0;
  float height = GetRenderHeight() / 2.0;
  float text_width = this->texture.width;
  float text_height = this->texture.height;

  std::cout << "WIDTH -> " << width << std::endl;
  std::cout << "HEIGHT -> " << height << std::endl;

  std::cout << "POS X -> " << this->position.x << std::endl;
  std::cout << "POS Y -> " << this->position.y << std::endl;

  float left_bound = width - 200;

  if (left_bound < this->position.x) {
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
