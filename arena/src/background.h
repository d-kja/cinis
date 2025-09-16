#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <array>
#include <iostream>
#include <raylib.h>

struct Background {
  Texture2D texture{};

  Vector2 last_position{};
  Vector2 position{};
  float rotation{};
  float scale{};

  std::array<float, 2> get_background_size();
  std::array<float, 2> get_background_center_offset();

  void clean_up_background();
  void setup_background(const char *path);
  void render_background(float char_width, float char_height);
  void handle_boundary();
};

struct Backgrounds {
  Background primary{};

  void setup_backgrounds();
  void clean_up_backgrounds();
  void render_backgrounds(float char_width, float char_height);
};

#endif // !BACKGROUND_H
