#include "game.h"
#include "raylib.h"

#include "static.h"
#include "window.h"

#include "character.h"
#include "collision.h"
#include "props.h"

void Game::setup() {
  InitWindow(width, height, title);

  SetTargetFPS(target_fps);
  // SetConfigFlags(FLAG_FULLSCREEN_MODE);
  // ToggleFullscreen();

  backgrounds.setup_backgrounds();
  character.setup();
  props.setup();

  Background *background_ref = &this->backgrounds.primary;
  Character *char_ref = &this->character;
  Props *props_ref = &this->props;

  collision.setup(char_ref, background_ref, props_ref);
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

  backgrounds.render_backgrounds();
  props.render(this->character.position, this->backgrounds.primary.position);
  character.render_character();

  character.handle_controller(&backgrounds);

  collision.handle_collision();

  EndDrawing();
}
