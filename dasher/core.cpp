#include "raylib.h"
#include <iostream>

struct Window {
  int width;
  int height;
  const char *title;
};

struct MovementOffset {
  const float positive;
  const float negative;
};

struct Engine {
  float delta;
  const float gravity;
  MovementOffset offset;
};

Window window = Window{.width = 1200, .height = 600, .title = "Dasher"};
Engine engine = Engine{
    .delta = 0.0,
    .gravity = 9.8,
    .offset =
        MovementOffset{
            .positive = 1.5,
            .negative = 1.0,
        },
};

const float animation_update_time = 1.0 / 12.0;

struct Animation {
  int frame;
  float running_time;
  const float update_time;
};

struct Sprite {
  const float sprites;
  Animation animation;

  float velocity; // force = mass * acceleration;

  Vector2 position;
  Texture2D texture;
  Rectangle rectangle;
};

Sprite character = Sprite{
    .sprites = 9.0,
    .animation = Animation{.frame = 0,
                           .running_time = 0.0,
                           .update_time = animation_update_time},
};

int get_floor_y(int height) { return window.height - height; }
int get_center_x() {
  return window.width / 2.0 - character.rectangle.width / 2;
}

int get_char_left_bound_x() { return character.position.x; }
int get_char_right_bound_x() {
  return character.position.x + character.rectangle.width;
}
int get_char_upper_bound_y() { return character.position.y; }
int get_char_lower_bound_y() {
  return character.position.y + character.rectangle.height;
}

bool is_floor() {
  return character.position.y >= get_floor_y(character.rectangle.height);
}

//
// Hazard
//

Sprite hazard = Sprite{
    .sprites = 8.0,
    .animation =
        Animation{
            .frame = 0,
            .running_time = 0.0,
            .update_time = animation_update_time,
        },
    .velocity = 150.0,
};

float print_debug = 0;
void debug_state() {
  print_debug += engine.delta;

  if (print_debug < 0.5) {
    return;
  }

  std::cout << "DELTA: " << engine.delta << std::endl;
  std::cout << "CHARACTER X: " << character.position.x << std::endl;
  std::cout << "CHARACTER Y: " << character.position.y << std::endl;
  std::cout << "GRAVITY: " << engine.gravity << std::endl;
  std::cout << "VELOCITY: " << character.velocity << std::endl;
  std::cout << "FLOOR: " << is_floor() << std::endl;

  print_debug = 0;
}

void reset_movement() { character.velocity = 0.0; }
void apply_gravity() { character.velocity += engine.gravity * engine.delta; }
void check_boundaries() {
  if (is_floor()) {
    character.position.y = get_floor_y(character.rectangle.height);
    character.velocity = 0;
  }
}

void character_controller() {
  debug_state();

  if (IsKeyPressed(KEY_SPACE) && is_floor()) {
    character.velocity -= 400.0 * engine.delta;
  }

  apply_gravity();
  character.position.y += character.velocity;

  check_boundaries();
}

void render_character() {
  character.animation.running_time += engine.delta;
  if (!is_floor()) {
    if (character.animation.running_time >= (animation_update_time * 4.0)) {
      character.animation.running_time = 0.0;
      character.animation.frame += 1;
    }
  } else {
    if (character.animation.running_time >= character.animation.update_time) {
      character.animation.running_time = 0.0;
      character.animation.frame += 1;
    }
  }

  if (character.animation.frame >= character.sprites) {
    character.animation.frame = 0;
  }

  character.rectangle.x = character.rectangle.width * character.animation.frame;

  DrawTextureRec(character.texture, character.rectangle, character.position,
                 WHITE);
}

void hazard_controller() {
  hazard.position.x -= hazard.velocity * engine.delta;

  if (hazard.position.x <= (hazard.rectangle.width * -1)) {
    hazard.position.x = window.width;
  }
}

void render_hazard() {
  hazard.animation.running_time += engine.delta;

  if (hazard.animation.running_time >= hazard.animation.update_time) {
    hazard.animation.running_time = 0.0;
    hazard.animation.frame += 1;
  }

  if (hazard.animation.frame >= hazard.sprites) {
    hazard.animation.frame = 0;
  }

  hazard.rectangle.x = hazard.rectangle.width * hazard.animation.frame;

  DrawTextureRec(hazard.texture, hazard.rectangle, hazard.position, WHITE);
}

void handle_hitbox() {
  int axis_offset = 30;
  int size_offset = 50;
}

void initialize_character() {
  character.texture = LoadTexture("./assets/character.png");

  character.rectangle.width = character.texture.width / character.sprites;
  character.rectangle.height = character.texture.height;
  character.rectangle.x = 0;
  character.rectangle.y = 0;

  character.position.x = get_center_x();
  character.position.y = get_floor_y(character.rectangle.height);
}

void initialize_hazard() {
  hazard.texture = LoadTexture("./assets/hazard.png");

  hazard.rectangle.width = hazard.texture.width / hazard.sprites;
  hazard.rectangle.height = hazard.texture.height / hazard.sprites;
  hazard.rectangle.x = 0;
  hazard.rectangle.y = 0;

  hazard.position.x = window.width;
  hazard.position.y = get_floor_y(hazard.rectangle.height);
}

void kill_game() {
  debug_state();

  UnloadTexture(character.texture);
  UnloadTexture(hazard.texture);

  CloseWindow();
}

int main() {
  InitWindow(window.width, window.height, window.title);
  SetTargetFPS(60);

  initialize_character();
  initialize_hazard();

  while (true) {
    bool shouldCloseWindow =
        WindowShouldClose(); //&& !IsKeyPressed(KEY_ESCAPE);

    if (shouldCloseWindow) {
      kill_game();
      return 0;
    }

    BeginDrawing();
    ClearBackground(WHITE);

    engine.delta = GetFrameTime();

    render_character();
    render_hazard();

    character_controller();
    hazard_controller();

    handle_hitbox();

    EndDrawing();
  }
}
