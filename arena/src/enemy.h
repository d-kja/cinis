#ifndef ENEMY
#define ENEMY

#include <raylib.h>
#include <string>
#include <vector>

#include "static.h"

struct Enemy {
public:
  Enemy(Texture2D running_texture, Texture2D idle_texture, Vector2 position);

  Rectangle sprite_position{};
  Rectangle window_position{};

  void clean_up();
  void render_enemy();

  void update_delta(float delta);

private:
  float delta{};
  float rotation{};
  Vector2 direction{};
  float scale{BASE_SCALE};

  Texture2D texture_idle{};
  Texture2D texture_running{};

  Texture2D texture{};

  float animation_frame{};
  float animation_time{};

  void update_position();
  void setup();
};

#endif // !ENEMY
