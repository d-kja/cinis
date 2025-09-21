#include "props.h"
#include "prop.h"
#include <raylib.h>

Props::Props() {}

void Props::setup() {
  Texture2D obstacle_01_texture = LoadTexture("assets/obstacle-02.png");
  Texture2D obstacle_02_texture = LoadTexture("assets/obstacle-01.png");

  Prop obstacle_01{obstacle_01_texture, Vector2{.x = 770.f, .y = 1280.f}};
  Prop obstacle_02{obstacle_02_texture, Vector2{.x = 2950.f, .y = 390.f}};

  this->props.push_back(obstacle_01);
  this->props.push_back(obstacle_02);
}

void Props::clean_up() {
  for (Prop prop : this->props) {
    prop.clean_up();
  }
}

void Props::render(Vector2 character_position, Vector2 world_position) {
  for (Prop prop : this->props) {
    prop.render(character_position, world_position);
  }
}
