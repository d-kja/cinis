#include "game.h"
#include "raylib.h"

#include "static.h"
#include "window.h"

#include "character.h"
#include "props.h"

void Game::setup() {
  InitWindow(width, height, title);

  SetTargetFPS(target_fps);
  // SetConfigFlags(FLAG_FULLSCREEN_MODE);
  // ToggleFullscreen();

  backgrounds.setup_backgrounds();
  character.setup();
  props.setup();
  props.setup();
};

void Game::clean_up() {
  backgrounds.clean_up_backgrounds();
  character.clean_up();
  props.clean_up();

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
  ClearBackground(BLACK);

  handle_resize_window();
  update_delta();

  if (WindowShouldClose()) {
    clean_up();

    playing = false;
    return;
  }

  backgrounds.render_backgrounds(this->character.texture,
                                 this->character.position);
  character.render_character();
  props.render(this->character.position, this->backgrounds.primary.position);

  character.handle_controller(&backgrounds);

  EndDrawing();
}
