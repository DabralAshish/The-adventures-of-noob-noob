#ifndef GAME_H
#define GAME_H

#include<vector>
#include <string>
#include<map>
#include <random>
// #include <SDL/SDL.h>
// #include <SDL/SDL_image.h>
#include "controller.h"
#include "renderer.h"
#include "noobnoob.h"
#include "levelmap.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, 
       std::size_t screen_width, std::size_t screen_height,
       std::vector<size_t> offset, std::string const res_path);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::vector<size_t> offset;
  Files files;
  std::vector<std::vector<int>> egp;
  std::vector<int> current_coins;
  
 private:
  NoobNoob noobnoob;
  std::map<std::string, SDL_Rect> artefacts;
  std::vector<int> const artefact_vals{0, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14};
  std::vector<int> const artefact_collect_states{0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0};
  std::vector<int> const artefact_pass_states{0, 0, 0, 0, 0, 1, 1, 1, 1, 0};
  LevelMap levelmap;
  std::random_device rd;      
  
  int score{0};
  
  void checkArtefacts();
  void placeCoins();
  void readArtefacts();
  void Update();
};

#endif