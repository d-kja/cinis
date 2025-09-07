#include "raylib.h"

#include "./character.cpp"
#include "./window.cpp"

struct Game {
  bool playing = true;
  float delta{};

  float *window_width = &width;
  float *window_height = &height;

  Character character{
      .window = {.width = window_width, .height = window_height}};
  Backgrounds backgrounds{};

  void setup() {
    InitWindow(width, height, title);

    SetTargetFPS(target_fps);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    ToggleFullscreen();

    backgrounds.setup_backgrounds();
    character.setup();
  };

  void clean_up() {
    // Unload assets
    backgrounds.clean_up_backgrounds();
    character.clean_up();

    CloseWindow();
  }

  void handle_resize_window() {
    bool should_resize = IsWindowResized();
    if (!should_resize) {
      return;
    }

    width = GetRenderWidth();
    height = GetRenderHeight();
  }

  void update_delta() {
    delta = GetFrameTime();

    character.update_delta(this->delta);
  }

  void runtime() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    handle_resize_window();
    update_delta();

    if (WindowShouldClose()) {
      clean_up();

      playing = false;
      return;
    }

    backgrounds.render_backgrounds();
    character.render_character();

    character.handle_controller(&backgrounds);

    EndDrawing();
  }
};
