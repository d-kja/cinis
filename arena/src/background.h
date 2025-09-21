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

  void render_background();
  void handle_collision(Vector2 character_position);

  std::array<Vector2, 2> get_center(Vector2 character_position);

  void revert_step();
};

struct Backgrounds {
  Background primary{};

  void setup_backgrounds();
  void clean_up_backgrounds();

  void render_backgrounds();
};

#endif // !BACKGROUND_H
