
#include "game.h"

#include "character.h"
#include "window.h"

#include "raylib.h"

// float* Game::window_width = &width;
// float* Game::window_height = &height;

void Game::setup() {
  InitWindow(width, height, title);

  SetTargetFPS(target_fps);
  // SetConfigFlags(FLAG_FULLSCREEN_MODE);
  // ToggleFullscreen();

  backgrounds.setup_backgrounds();
  character.setup();
};

void Game::clean_up() {
  // Unload assets
  backgrounds.clean_up_backgrounds();
  character.clean_up();

  CloseWindow();
}

void Game::handle_resize_window() {
  bool should_resize = IsWindowResized();
  if (!should_resize) {
    return;
  }

  width = GetRenderWidth();
  height = GetRenderHeight();
}

void Game::update_delta() {
  delta = GetFrameTime();

  character.update_delta(this->delta);
}

void Game::runtime() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  handle_resize_window();
  update_delta();

  if (WindowShouldClose()) {
    clean_up();

    playing = false;
    return;
  }

  backgrounds.render_backgrounds(character.texture.width,
                                 character.texture.height);
  character.render_character();

  character.handle_controller(&backgrounds);

  EndDrawing();
}

// Window* heap_window = new Window{100.f, 200.f};  // Heap allocation (new /
// malloc) float* heap_width = &heap_window->width; // pointer that needs to be
// freed, cuz heap value;
//
// delete heap_window; -> dangling
// heap_window = nullptr;
