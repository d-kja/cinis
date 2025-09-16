#ifndef GAME_H
#define GAME_H

#include "prop.h"
#include "raylib.h"

#include "background.h"
#include "character.h"
#include "window.h"

struct Game {
  bool playing{true};
  float delta{};

  // float& window... = width -> only a reference.
  float *window_width = &width;
  float *window_height = &height;

  Character character{{.width = window_width, .height = window_height}};
  std::vector<Prop> props{};
  Backgrounds backgrounds;

  void setup();
  void clean_up();

  void handle_resize_window();
  void update_delta();

  void runtime();
};

// Window* heap_window = new Window{100.f, 200.f};  // Heap allocation (new /
// malloc) float* heap_width = &heap_window->width; // pointer that needs to be
// freed, cuz heap value;
//
// delete heap_window; -> dangling
// heap_window = nullptr;

#endif // !GAME_H
