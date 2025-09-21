#include "prop.h"
#include <raylib.h>
#include <raymath.h>

Prop::Prop(Texture2D texture, Vector2 position)
    : texture(texture), position(position) {}

void Prop::render(Vector2 character_position, Vector2 world_position) {
  Vector2 new_position = Vector2Add(
      this->position, Vector2Subtract(world_position, character_position));
  this->position = new_position;

  DrawTextureEx(this->texture, this->position, this->rotation, this->scale,
                RAYWHITE);
}

void Prop::clean_up() { UnloadTexture(this->texture); }
