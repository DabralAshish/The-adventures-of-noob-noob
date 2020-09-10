#ifndef NoobNoob_H
#define NoobNoob_H

#include <vector>
#include "SDL.h"

class NoobNoob {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  NoobNoob(int grid_width, int grid_height, int screen_width, int screen_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        screen_width(screen_width),
        screen_height(screen_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  //void GrowBody();
  bool NoobNoobCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  int screen_width;
  int screen_height;
};

#endif