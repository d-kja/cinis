#include "raylib.h"

#include "./window.cpp"

#include "./background.cpp"
#include "./character.cpp"

struct Game {
  bool playing = true;
  float delta{};

  Character character{};
  Backgrounds backgrounds{};

  void setup() {
    InitWindow(width, height, title);

    SetTargetFPS(target_fps);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);

    ToggleFullscreen();

    backgrounds.setup_backgrounds();
  };

  void clean_up() {
    // Unload assets
    backgrounds.clean_up_backgrounds();

    // CloseAudioDevice();
    CloseWindow();
  }

  void handle_resize() {
    bool should_resize = IsWindowResized();
    if (!should_resize) {
      return;
    }

    width = GetRenderWidth();
    height = GetRenderHeight();
  }

  void runtime() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    handle_resize();
    delta = GetFrameTime();

    if (WindowShouldClose()) {
      clean_up();

      playing = false;
      return;
    }

    backgrounds.render_backgrounds();

    EndDrawing();
  }
};
