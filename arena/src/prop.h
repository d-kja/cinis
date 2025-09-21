#ifndef PROP
#define PROP

#include "raylib.h"
#include "static.h"

struct Prop {
public:
  Prop(Texture2D texture, Vector2 positon);
  void render(Vector2 character_position, Vector2 world_position);
  void clean_up();

private:
  Texture2D texture{};
  Vector2 position{};

  float scale{BASE_SCALE};
  float rotation{0.f};
};

#endif // !PROP
