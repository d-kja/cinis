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
  void render_background(Texture2D character_texture, Vector2 character_position);
  void handle_boundary(Vector2 character_position);
};

struct Backgrounds {
  Background primary{};

  void setup_backgrounds();
  void clean_up_backgrounds();
  void render_backgrounds(Texture2D char_texture, Vector2 char_position);
};

#endif // !BACKGROUND_H
