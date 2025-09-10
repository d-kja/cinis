#ifndef CHARACTER_H
#define CHARACTER_H

#include "background.h"

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

extern const float BASE_SPEED;
extern const float AMOUNT_SPRITES; 
extern const float ANIMATION_TIME_BASE;

struct Damage {
  float health{};
  std::string origin{};
};

struct _Window {
  float *width;
  float *height;
};

struct Character {
  _Window window{};

  float delta{};
  float speed{0.75};

  float animation_time{0.0};
  float animation_frame{0.0};

  Vector2 direction{};
  float health{10.0};
  float level{0.0};

  std::vector<Damage> damage_taken = {};

  const float sprites{AMOUNT_SPRITES};

  Texture2D texture_idle{};
  Texture2D texture_running{};

  Texture2D texture{};
  Rectangle sprite_position{};

  Vector2 position{};
  Rectangle window_position{};

  void handle_controller(Backgrounds *backgrounds);
  void update_position();

  void render_character();
  void update_delta(float delta);

  void setup();
  void clean_up();
};

#endif // !CHARACTER_H
