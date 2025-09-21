#include "collision.h"
#include <raylib.h>
#include <raymath.h>

#include "static.h"

void Collision::setup(Character *character, Background *background,
                      Props *props) {
  this->background = background;
  this->character = character;
  this->props = props;
}

bool Collision::check_collision() {
  for (auto prop : this->props->get_props()) {
    auto center = background->get_center(this->character->position);
    Vector2 prop_origin =
        Vector2Subtract(this->character->position, prop.position);

    Rectangle character_position{
        .x = center[0].x * -1.f,
        .y = center[0].y * -1.f,
        .width = static_cast<float>(this->character->texture.width) / AMOUNT_SPRITES,
        .height = static_cast<float>(this->character->texture.height),
    };
    Rectangle prop_position{
        .x = prop_origin.x * -1.f - 10.f,
        .y = prop_origin.y * -1.f - 15.f,
        .width = prop.texture.width * BASE_SCALE + 30.f,
        .height = prop.texture.height * BASE_SCALE,
    };

    bool has_collided = CheckCollisionRecs(character_position, prop_position);
    if (!has_collided) {
      continue;
    }

    return has_collided;
  }

  return false;
}

void Collision::handle_collision() {
  this->background->handle_collision(this->character->position);

  bool has_collided = this->check_collision();
  if (has_collided) {
    this->background->revert_step();
  }
}
