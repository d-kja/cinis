#include <array>
#include <raylib.h>
struct _background {
  Texture2D texture{};

  Vector2 position{};
  Rectangle rectangle{};

  std::array<float, 2> get_center_axis(float width, float height) {
    float x_axis = width / 2 * -1;
    float y_axis = height / 2 * -1;

    std::array<float, 2> arr = {x_axis, y_axis};
    return arr;
  }

  void clean_up_background() { UnloadTexture(this->texture); }
  void setup_background(const char *path) {
    this->texture = LoadTexture(path);

    std::array<float, 2> axis =
        this->get_center_axis(this->texture.width, this->texture.height);

    this->position.x = 0.0; // axis[0];
    this->position.y = 0.0; // axis[1];

    this->rectangle.width = this->texture.width;
    this->rectangle.height = this->texture.height;
    this->rectangle.x = 0.0;
    this->rectangle.y = 0.0;
  }

  void render_background() {
    DrawTextureRec(this->texture, this->rectangle, this->position, RAYWHITE);
  }
};

struct Backgrounds {
  _background primary{};

  void setup_backgrounds() { this->primary.setup_background("assets/map.png"); }
  void clean_up_backgrounds() { this->primary.clean_up_background(); }
  void render_backgrounds() { this->primary.render_background(); }
};
