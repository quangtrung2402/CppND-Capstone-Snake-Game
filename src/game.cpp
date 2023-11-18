#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake_1(grid_width, grid_height, grid_width * 1 / 3, grid_height),
      snake_2(grid_width, grid_height, grid_width * 2 / 3, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake_1, snake_2);
    Update();
    renderer.Render(snake_1, snake_2, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      std::string title{"Green snake: " + std::to_string(snake_1.GetBodySize())
                      + " <==> Blue snake: " + std::to_string(snake_2.GetBodySize())
                      + " | FPS: " + std::to_string(frame_count)};
      renderer.UpdateWindowTitle(title);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake_1.SnakeCell(x, y) && !snake_2.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake_1.Alive() || !snake_2.Alive()) return;

  snake_1.Update();
  snake_2.Update();

  // Check if there's food over here
  if (snake_1.EatFood(food) || snake_2.EatFood(food)) {
    PlaceFood();
  }
}

void Game::PrintResult() const {
  std::cout << "Green player's score: " << snake_1.GetBodySize() << "\n";
  std::cout << "Blue player's score : " << snake_2.GetBodySize() << "\n";
}