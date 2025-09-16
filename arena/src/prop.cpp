#include "prop.h"
#include <raylib.h>
#include <raymath.h>

Prop::Prop(Rectangle rectangle, Vector2 position)
    : rectangle(rectangle), position(position) {}

void Prop::render(Vector2 character_position, Vector2 world_position) {
  Vector2 new_position = Vector2Add(this->position, Vector2Subtract(world_position, character_position));
  this->position = new_position;

  DrawRectangle(this->position.x, this->position.y, this->rectangle.width,
                this->rectangle.height, RED);
}

void Prop::clean_up() {
  // if (this->texture) {
  //   return;
  // }
  //
  // UnloadTexture(this->texture);
}
