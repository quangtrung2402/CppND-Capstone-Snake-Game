#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake_1, Snake &snake_2) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input) const;
};

#endif