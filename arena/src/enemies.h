#ifndef ENEMIES
#define ENEMIES

#include <vector>

#include "enemy.h"

struct Enemies {
  public:
  std::vector<Enemy> enemies{};

  void setup();

  void render();
  void clean_up();

  void update_delta(float delta);

  private: 
};

#endif // !ENEMIES
