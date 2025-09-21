#ifndef PROP
#define PROP

#include "raylib.h"
#include "static.h"

struct Prop {
public:
  float scale{BASE_SCALE};
  Texture2D texture{};
  Vector2 position{};
  float rotation{0.f};

  Prop(Texture2D texture, Vector2 positon);

  void render(Vector2 character_position, Vector2 world_position);
  void clean_up();

private:
};

#endif // !PROP
