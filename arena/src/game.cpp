#include "game.h"
#include "prop.h"
#include "raylib.h"

#include "character.h"
#include "static.h"
#include "window.h"

void Game::setup() {
  InitWindow(width, height, title);

  SetTargetFPS(target_fps);
  // SetConfigFlags(FLAG_FULLSCREEN_MODE);
  // ToggleFullscreen();

  backgrounds.setup_backgrounds();
  character.setup();

  Prop red_prop{Rectangle{.x = 0, .y = 0.f, .width = 380.f, .height = 400.f},
                Vector2{.x = 770.f, .y = 1280.f}};

  Prop red_prop_2{
      Rectangle{.x = 0.f, .y = 0.f, .width = 250.f, .height = 400.f},
      Vector2{.x = 2000.f, .y = 800.f}};

  this->props.push_back(red_prop);
  this->props.push_back(red_prop_2);
};

void Game::clean_up() {
  backgrounds.clean_up_backgrounds();
  character.clean_up();

  for (Prop prop : this->props) {
    prop.clean_up();
  }

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
  for (Prop prop : this->props) {
    prop.render(this->character.position, this->backgrounds.primary.position);
  }

  character.handle_controller(&backgrounds);

  EndDrawing();
}
