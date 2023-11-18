# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

## New features

* Allow players to change the speed of the game.
  * The speed of the game start by 0.0
  * The speed will change when user change from terminal
* Add another snake to the game
  * The game can play by two players
  * First player can control their snake by W-A-S-D keys
  * Second player can control their snake by direction keys
  * The game will stop if an snake is eaten by itself

## Rubric point

### 1. Loops, Functions, I/O - meet at least 2 criteria

* The project demonstrates an understanding of C++ functions and control structures
  * switch control: __Snake::UpdateHead()__, __Controller::ChangeDirection(Snake &snake, Snake::Direction input)__
  * Add move functions in the snake class: ___snake.h___
* The project accepts user input and processes the input
  * Add keyboard input to control the new snake: __Controller::HandleInput(bool &running, Snake &green_snake, Snake &blue_snake)__

### 2. Object Oriented Programming - meet at least 3 criteria

* Class constructors utilize member initialization lists.
  * Initialize the snake color: __Snake(SDL_Color color, int grid_width, int grid_height, int head_x, int head_y)__
* The project uses data structures and immutable variables.
  * Use colors in the snake

### 3. Memory Management - meet at least 3 criteria

* The project makes use of references in function declarations.
  * Use references at: __Snake::EatFood(const SDL_Point &food)__

### 4. Concurrency - meet at least 2 criteria

* The project uses multithreading.
  * game.cpp: 22
* A mutex or lock is used in the project.
  * snake.h: 50
  * snake.cpp: 23, 86