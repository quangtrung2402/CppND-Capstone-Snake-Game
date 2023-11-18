#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : green_snake({0x00, 0xFF, 0x00, 0xFF}, grid_width, grid_height, grid_width * 1 / 3, grid_height),
      blue_snake({0x00, 0x00, 0xFF, 0xFF}, grid_width, grid_height, grid_width * 2 / 3, grid_height),
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

  UpdateSpeed();
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, green_snake, blue_snake);
    Update();
    renderer.Render(green_snake, blue_snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      std::string title{"Green snake: " + std::to_string(green_snake.GetBodySize())
                      + " <==> Blue snake: " + std::to_string(blue_snake.GetBodySize())
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
    if (!green_snake.SnakeCell(x, y) && !blue_snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!green_snake.Alive() || !blue_snake.Alive()) return;

  green_snake.Update();
  blue_snake.Update();

  // Check if there's food over here
  if (green_snake.EatFood(food) || blue_snake.EatFood(food)) {
    PlaceFood();
  }
}

void Game::PrintResult() const {
  std::cout << "Green player's score: " << green_snake.GetBodySize() << "\n";
  std::cout << "Blue player's score : " << blue_snake.GetBodySize() << "\n";
}

void Game::UpdateSpeed() {
  static auto GetInput = [&]() -> float {
    int speed = 0;
    while (speed == 0) {
      std::cin >> speed;
      if (speed < 0 || speed > 100) {
        speed = 0;
      }
    }
    return 0.1 + speed / 100.0f;
  };

  std::cout << "Please input a number for snake run (0 ~ 100): ";
  {
    float speed_input = GetInput();
    // std::cin >> speed_input;
    green_snake.SetSpeed(speed_input);
    blue_snake.SetSpeed(speed_input);
  }

  speed_input = std::thread([&]() mutable {
    while (running) {
      std::cout << "You can change snake's speed if you want. The new speed (0 ~ 100) is: ";
      auto speed = GetInput();
      // std::cin >> speed;
      green_snake.SetSpeed(speed);
      blue_snake.SetSpeed(speed);
    }
  });
  speed_input.detach();
}
