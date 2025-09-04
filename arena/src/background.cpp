#include <array>
#include <raylib.h>

const float BASE_SCALE = 4.0;

struct _background {
  Texture2D texture{};

  Vector2 position{};
  float rotation{};
  float scale{BASE_SCALE};

  std::array<float, 2> get_axis(float width, float height) {
    float x_axis = width * BASE_SCALE;
    float y_axis = height * BASE_SCALE;

    std::array<float, 2> arr = {x_axis, y_axis};
    return arr;
  }

  std::array<float, 2> get_center_axis(float width, float height) {
    std::array<float, 2> arr = this->get_axis(width, height);

    arr[0] /= 2;
    arr[1] /= 2;

    return arr;
  }

  void clean_up_background() { UnloadTexture(this->texture); }
  void setup_background(const char *path) {
    this->texture = LoadTexture(path);

    std::array<float, 2> axis =
        this->get_axis(this->texture.width, this->texture.height);

    float width = GetRenderWidth();
    float height = GetRenderHeight();

    // CENTER BACKGROUND
    float center_x = (width - axis[0]) / 2.0; 
    float center_y = (height - axis[1]) / 2.0;

    this->position.x = center_x;
    this->position.y = center_y;
  }

  void render_background() {
    DrawTextureEx(this->texture, this->position, this->rotation, this->scale,
                  RAYWHITE);
  }
};

struct Backgrounds {
  _background primary{};

  void setup_backgrounds() { this->primary.setup_background("assets/map.png"); }
  void clean_up_backgrounds() { this->primary.clean_up_background(); }
  void render_backgrounds() { this->primary.render_background(); }
};
