#include "raylib.h"
#include <iterator>

struct Window {
  int dimensions[2];
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

Window window = Window{.dimensions = {1200, 600}, .title = "Dasher"};
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
  float update_time;
};

struct Sprite {
  float sprites;
  Animation animation;

  float velocity; // force = mass * acceleration;

  Vector2 position;
  Texture2D texture;
  Rectangle rectangle;
};

struct Background {
  float velocity;
  float scale;
  float rotation;
  Vector2 position;
  Texture2D texture;
};

float get_scale(float width) { return window.dimensions[0] / width; };
float base_scale = get_scale(350.0);
const float base_velocity_backgrounds = 20.0;
const int amount_backgrounds = 2;

Texture2D background_texture;
Texture2D foreground_texture;
Texture2D alt_foreground_texture;

Background backgrounds[amount_backgrounds] = {
    {.velocity = base_velocity_backgrounds,
     .scale = base_scale,
     .rotation = 0.0,
     .position = Vector2{0.0, 0.0}},
    {.velocity = base_velocity_backgrounds,
     .scale = base_scale,
     .rotation = 0.0,
     .position = Vector2{0.0, 0.0}}};

Background alt_foregrounds[amount_backgrounds] = {
    {.velocity = base_velocity_backgrounds * 2,
     .scale = base_scale,
     .rotation = 0.0,
     .position = Vector2{0.0, 0.0}},
    {.velocity = base_velocity_backgrounds * 2,
     .scale = base_scale,
     .rotation = 0.0,
     .position = Vector2{0.0, 0.0}},
};

Background foregrounds[amount_backgrounds] = {
    {.velocity = base_velocity_backgrounds * 4,
     .scale = base_scale,
     .rotation = 0.0,
     .position = Vector2{0.0, 0.0}},
    {.velocity = base_velocity_backgrounds * 4,
     .scale = base_scale,
     .rotation = 0.0,
     .position = Vector2{0.0, 0.0}}};

Sprite hazards[4] = {};
Texture hazard_texture;

Sprite character = Sprite{
    .sprites = 9.0,
    .animation = Animation{.frame = 0,
                           .running_time = 0.0,
                           .update_time = animation_update_time},
};

bool has_died = false;
bool is_playing = true;
float finish_line_question_mark;

int get_floor_y(int height) { return window.dimensions[1] - height; }
int get_center_x() {
  return window.dimensions[0] / 2.0 - character.rectangle.width / 2;
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

void reset_movement() { character.velocity = 0.0; }
void apply_gravity() { character.velocity += engine.gravity * engine.delta; }
void check_boundaries() {
  if (is_floor()) {
    character.position.y = get_floor_y(character.rectangle.height);
    character.velocity = 0;
  }
}

void character_controller() {
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
  for (int idx = 0; idx < std::size(hazards); idx++) {
    Sprite hazard = hazards[idx];

    hazard.position.x -= hazard.velocity * engine.delta;
    if (hazard.position.x <= hazard.rectangle.width * -1) {
      hazard.position.x = window.dimensions[0];
    }

    hazards[idx] = hazard;
  }
}

void render_hazard() {
  for (int idx = 0; idx < std::size(hazards); idx++) {
    Sprite hazard = hazards[idx];
    hazard.animation.running_time += engine.delta;

    if (hazard.animation.running_time >= hazard.animation.update_time) {
      hazard.animation.running_time = 0.0;
      hazard.animation.frame += 1;
    }

    if (hazard.animation.frame >= hazard.sprites) {
      hazard.animation.frame = 0;
    }

    hazard.position.y = get_floor_y(hazard.rectangle.height);
    hazard.rectangle.x = hazard.rectangle.width * hazard.animation.frame;

    Color colors[4] = {WHITE, RED, BLUE, GREEN};
    int colors_size = std::size(colors);

    Color color_choice = colors[idx % colors_size];

    hazards[idx] = hazard;
    DrawTextureRec(hazard.texture, hazard.rectangle, hazard.position,
                   color_choice);
  }
}

void handle_resize() {
  window.dimensions[0] = GetRenderWidth();
  window.dimensions[1] = GetRenderHeight();

  character.position.y = get_floor_y(character.rectangle.height);

  for (int idx = 0; idx < std::size(backgrounds); idx++) {
    Background background = backgrounds[idx];

    base_scale = get_scale(background.texture.width);
    backgrounds[idx].scale = base_scale;
  }

  for (int idx = 0; idx < std::size(alt_foregrounds); idx++) {
    Background background = alt_foregrounds[idx];

    base_scale = get_scale(background.texture.width);
    alt_foregrounds[idx].scale = base_scale;
  }

  for (int idx = 0; idx < std::size(foregrounds); idx++) {
    Background background = foregrounds[idx];

    base_scale = get_scale(background.texture.width);
    foregrounds[idx].scale = base_scale;
  }
}

void handle_hitbox() {
  int axis_offset = 40;
  int size_offset = 70;

  for (Sprite hazard : hazards) {
    Rectangle enemy{
        .x = hazard.position.x + axis_offset,
        .y = hazard.position.y + axis_offset,

        // Wrong, but it's working lol
        .width = hazard.rectangle.width - size_offset * 2,
        .height = hazard.rectangle.height - size_offset * 2,

        // The correct thing to do!
        // .width = hazard.rectangle.width - size_offset * 2,
        // .height = hazard.rectangle.height - size_offset * 2,
    };

    Rectangle target{
        .x = character.position.x + axis_offset * 2,
        .y = character.position.y + axis_offset,
        .width = character.rectangle.width - size_offset * 2,
        .height = character.rectangle.height - size_offset,
    };

    bool has_collided = CheckCollisionRecs(enemy, target);

    if (has_collided) {
      has_died = true;
    }
  }
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
  hazard_texture = LoadTexture("./assets/hazard.png");

  for (int idx = 0; idx < std::size(hazards); idx++) {
    Sprite hazard = {
        .sprites = 8.0,
        .animation =
            Animation{
                .frame = 0,
                .running_time = 0.0,
                .update_time = animation_update_time,
            },
        .velocity = 150.0,
    };

    hazard.texture = hazard_texture;

    hazard.rectangle.width = hazard.texture.width / hazard.sprites;
    hazard.rectangle.height = hazard.texture.height / hazard.sprites;
    hazard.rectangle.x = 0;
    hazard.rectangle.y = 0;

    hazard.position.x =
        window.dimensions[0] + (idx * (window.dimensions[0] / 4.0));
    hazard.position.y = get_floor_y(hazard.rectangle.height);

    hazards[idx] = hazard;
  }
}

void render_backgrounds() {
  for (int idx = 0; idx < std::size(backgrounds); idx++) {
    Background background = backgrounds[idx];
    background.position.x -= background.velocity * engine.delta;

    if (background.position.x <=
        (background.texture.width * background.scale * -1)) {
      background.position.x = background.texture.width * base_scale * idx;
    }

    backgrounds[idx] = background;
    DrawTextureEx(background.texture, background.position, background.rotation,
                  background.scale, GRAY);
  }

  for (int idx = 0; idx < std::size(alt_foregrounds); idx++) {
    Background alt_foreground = alt_foregrounds[idx];
    alt_foreground.position.x -= alt_foreground.velocity * engine.delta;

    if (alt_foreground.position.x <=
        (alt_foreground.texture.width * alt_foreground.scale * -1)) {
      alt_foreground.position.x = alt_foreground.texture.width * base_scale;
    }

    alt_foregrounds[idx] = alt_foreground;
    DrawTextureEx(alt_foreground.texture, alt_foreground.position,
                  alt_foreground.rotation, alt_foreground.scale, GRAY);
  }

  for (int idx = 0; idx < std::size(foregrounds); idx++) {
    Background foreground = foregrounds[idx];
    foreground.position.x -= foreground.velocity * engine.delta;

    if (foreground.position.x <=
        (foreground.texture.width * foreground.scale * -1)) {
      foreground.position.x = foreground.texture.width * base_scale * idx;
    }

    foregrounds[idx] = foreground;
    DrawTextureEx(foreground.texture, foreground.position, foreground.rotation,
                  foreground.scale, WHITE);
  }
}

void initialize_backgrounds() {
  background_texture = LoadTexture("./assets/background.png");
  foreground_texture = LoadTexture("./assets/foreground.png");
  alt_foreground_texture = LoadTexture("./assets/alt-foreground.png");

  for (int idx = 0; idx < std::size(backgrounds); idx++) {
    Background background = backgrounds[idx];

    background.texture = background_texture;
    background.position.x = background_texture.width * base_scale * idx;

    backgrounds[idx] = background;
  }

  for (int idx = 0; idx < std::size(foregrounds); idx++) {
    Background foreground = foregrounds[idx];

    foreground.texture = foreground_texture;
    foreground.position.x = foreground_texture.width * base_scale * idx;

    foregrounds[idx] = foreground;
  }

  for (int idx = 0; idx < std::size(alt_foregrounds); idx++) {
    Background alt_foreground = foregrounds[idx];

    alt_foreground.texture = alt_foreground_texture;
    alt_foreground.position.x = alt_foreground_texture.width * base_scale * idx;

    alt_foregrounds[idx] = alt_foreground;
  }
}

void kill_game() {
  UnloadTexture(character.texture);
  UnloadTexture(hazard_texture);

  UnloadTexture(background_texture);
  UnloadTexture(foreground_texture);
  UnloadTexture(alt_foreground_texture);

  CloseWindow();
}

int main() {
  InitWindow(window.dimensions[0], window.dimensions[1], window.title);
  SetTargetFPS(60);

  initialize_hazard();
  initialize_character();
  initialize_backgrounds();

  finish_line_question_mark = foreground_texture.width * base_scale * 2;

  while (true) {
    bool shouldCloseWindow =
        WindowShouldClose(); //&& !IsKeyPressed(KEY_ESCAPE);
                             //
    if (shouldCloseWindow) {
      kill_game();
      return 0;
    }

    if (IsWindowResized()) {
      handle_resize();
    }

    BeginDrawing();
    ClearBackground(WHITE);

    engine.delta = GetFrameTime();

    render_backgrounds();
    render_character();
    render_hazard();

    if (has_died) {
      DrawText("HAS DIED", (window.dimensions[0] - 44 * 4) / 2,
               (window.dimensions[1] - 44) / 2, 44, RED);

      EndDrawing();
      continue;
    }

    if (!is_playing) {
      DrawText("YOU FINISHED!", (window.dimensions[0] - 44 * 4) / 2,
               (window.dimensions[1] - 88) / 2, 44, WHITE);

      EndDrawing();
      continue;
    }

    finish_line_question_mark -=
        base_velocity_backgrounds * 4 * engine.delta * amount_backgrounds;
    if (finish_line_question_mark <= 0) {
      is_playing = false;
    }

    character_controller();
    hazard_controller();

    handle_hitbox();

    EndDrawing();
  }
}
