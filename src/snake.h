#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kNone, kUp, kDown, kLeft, kRight };

  Snake(SDL_Color color, int grid_width, int grid_height, int head_x, int head_y)
      : color(color),
        grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_x),
        head_y(head_y) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  void SpeedUp();
  void Up();
  void Down();
  void Left();
  void Right();
  bool Alive() const;
  bool EatFood(const SDL_Point &food);
  SDL_Point GetHead() const;
  std::vector<SDL_Point> GetBody() const;
  int GetBodySize() const;
  const SDL_Color &GetColor() const;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  const SDL_Color color;
  bool growing{false};
  int grid_width;
  int grid_height;
  float speed{0.1f};
  Direction direction = Direction::kNone;
  int body_size{0};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
};

#endif