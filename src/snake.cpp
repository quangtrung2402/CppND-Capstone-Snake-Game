#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
    case Direction::kNone:
      // Snake doesn't move, so we don't need to update the head
      return;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::SpeedUp() {
  speed += 0.02;
}

void Snake::Up() {
  if (direction != Snake::Direction::kDown || size == 1)
    direction = Snake::Direction::kUp;
}

void Snake::Down() {
  if (direction != Snake::Direction::kUp || size == 1)
    direction = Snake::Direction::kDown;
}

void Snake::Left() {
  if (direction != Snake::Direction::kRight || size == 1)
    direction = Snake::Direction::kLeft;
}

void Snake::Right() {
  if (direction != Snake::Direction::kLeft || size == 1)
    direction = Snake::Direction::kRight;
}

bool Snake::Alive() const {
  return alive;
}

bool Snake::EatFood(const SDL_Point &food) {
  // Check if there's food over here
  if (food.x == static_cast<int>(head_x) && food.y == static_cast<int>(head_y)) {
    // Grow snake and increase speed.
    GrowBody();
    SpeedUp();
    return true;
  }
  return false;
}

SDL_Point Snake::GetHead() const {
  return SDL_Point{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};
}

std::vector<SDL_Point> Snake::GetBody() const {
  return body;
}