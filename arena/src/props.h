#ifndef PROPS
#define PROPS

#include "prop.h"
#include <vector>

struct Props {
public:
  Props();

  void clean_up();
  void setup();

  void render(Vector2 character_position, Vector2 world_position);

private:
  std::vector<Prop> props;
};

#endif // !PROPS
