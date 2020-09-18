#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
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
  
 private:
  NoobNoob noobnoob;
  SDL_Point artefact;
  LevelMap levelmap;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceArtefact();
  void Update();
};

#endif