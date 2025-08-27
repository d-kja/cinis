#include "raylib.h"
#include <iostream>

int velocity = 400;

int main() {
  int width = 1200;
  int height = 600;
  bool muahahahah = true;

  const char *title = "Example";

  InitWindow(width, height, title);

  float movement_positive_offset = 1.5;
  float movement_negative_offset = 1.0;

  int circle_x = width / 2;
  int circle_y = height / 2;
  int circle_radius = 30;

  int rec_x = 300;
  int rec_y = 0;
  int rec_size = 50;

  int flip = 1;

  bool is_playing = true;

  while (muahahahah) {
    if (WindowShouldClose()) {
      return 0;
    }

    BeginDrawing();
    ClearBackground(WHITE); // Reset default

    float delta = GetFrameTime();
    std::cout << "Delta time: " << delta << std::endl;

    if (is_playing) {

      // Our character wow
      DrawCircle(circle_x, circle_y, circle_radius, RED);
      DrawRectangle(rec_x, rec_y, rec_size, rec_size, BLUE);

      //
      // BOUNDS
      //

      bool is_left_bound = circle_x <= circle_radius;
      bool is_right_bound = circle_x >= (width - circle_radius);

      bool is_top_bound = circle_y <= circle_radius;
      bool is_bottom_bound = circle_y >= (height - circle_radius);

      int circle_lbound = circle_x - circle_radius;
      int circle_rbound = circle_x + circle_radius;
      int circle_ubound = circle_y - circle_radius;
      int circle_bbound = circle_y + circle_radius;

      int axe_lbound = rec_x;
      int axe_rbound = rec_x + rec_size;
      int axe_ubound = rec_y;
      int axe_bbound = rec_y + rec_size;

      int x_axis_collision =
          (circle_lbound <= axe_rbound && circle_lbound >= axe_lbound) ||
          (circle_rbound >= axe_lbound && circle_rbound <= axe_rbound);
      int y_axis_collision =
          (circle_ubound <= axe_bbound && circle_ubound >= axe_ubound) ||
          (circle_bbound >= axe_ubound && circle_bbound <= axe_bbound);

      if (x_axis_collision && y_axis_collision) {
        is_playing = false;
      }

      //
      // MOVEMENTS
      //

      // UP
      if (IsKeyDown(KEY_W) && !is_top_bound) {
        circle_y -= (movement_negative_offset * velocity * delta);
      }

      // DOWN
      if (IsKeyDown(KEY_S) && !is_bottom_bound) {
        circle_y += (movement_positive_offset * velocity * delta);
      }

      // RIGHT
      if (IsKeyDown(KEY_D) && !is_right_bound) {
        circle_x += (movement_positive_offset * velocity * delta);
      }

      // LEFT
      if (IsKeyDown(KEY_A) && !is_left_bound) {
        circle_x -= (movement_negative_offset * velocity * delta);
      }

      rec_y += (movement_negative_offset * (velocity / 1.15  * 2) * delta) * flip;

      bool reached_bottom_bound = rec_y >= (height - (rec_size / 2));
      bool reached_top_bound = rec_y <= (rec_size / 2);

      if (reached_bottom_bound) {
        flip = -1;
      }

      if (reached_top_bound) {
        flip = 1;
      }
    } else {
      DrawText("Game Over!", width / 2 - 60, height / 2 - 30, 30, RED);
    }

    EndDrawing();
  }

  return 0;
}

// bool b{1 > 0};
