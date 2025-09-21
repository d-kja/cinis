#ifndef COLLISION
#define COLLISION

#include <raylib.h>

#include "background.h"
#include "character.h"
#include "props.h"

struct Collision {
public:
  void setup(Character *character, Background *background, Props *props);

  void handle_collision();
  bool check_collision();

private:
  Background *background;
  Character *character;
  Props *props;
};

#endif // !COLLISION
