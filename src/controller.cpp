#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input) const {
  switch (input) {
    case Snake::Direction::kUp:     snake.Up();     break;
    case Snake::Direction::kDown:   snake.Down();   break;
    case Snake::Direction::kLeft:   snake.Left();   break;
    case Snake::Direction::kRight:  snake.Right();  break;
    default: break;
  }
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight);
          break;
      }
    }
  }
}