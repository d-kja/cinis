#ifndef PROP
#define PROP

#include "raylib.h"
#include "static.h"

struct Prop {
public:
  Prop(Rectangle rectangle, Vector2 positon);
  void render(Vector2 character_position, Vector2 world_position);
  void clean_up();

private:
  Rectangle rectangle{};
  Vector2 position{};

  float scale{BASE_SCALE};
};

#endif // !PROP
