#ifndef NoobNoob_H
#define NoobNoob_H

#include <vector>
#include <chrono>
#include "SDL.h"
#include "levelmap.h"

class NoobNoob {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  NoobNoob(int grid_width, int grid_height, int screen_width, int screen_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        screen_width(screen_width),
        screen_height(screen_height),
        head_x(0),
        head_y(0){};

  void Update();

  //void GrowBody();
  bool NoobNoobCell(int x, int y);

  Direction direction = Direction::kUp;
  bool hasDirectionChanged = false;

  float speed{1.0f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  LevelMap levelmap;
  
  std::vector<int> artefact_vals;
  std::vector<int> artefact_collect_states;
  std::vector<int> artefact_pass_states;
  
  bool is_buddha = false;
  bool is_key = false;
  bool is_soup = false;
  int nc = 5;
  //Enable noobnoob parameter.
  bool enable_story = false;
  bool enable_noobnoob = false;
  int count_enables = 0;
  std::string hint=" ";
  bool is_accessible = false;
  
 private:
  void UpateNoobNoob();

  int grid_width;
  int grid_height;
  int screen_width;
  int screen_height;
  
  std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
};

#endif