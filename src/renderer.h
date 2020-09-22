#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL_ttf.h>
#include "noobnoob.h"
#include "levelmap.h"
#include "files.h"

class Renderer {
 public:
  Renderer(const std::size_t top_bar_height, const std::size_t top_bar_width,
           const std::size_t game_width, const std::size_t game_height,
           const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(NoobNoob const noobnoob, std::map<std::string, SDL_Rect> artefacts, LevelMap levelmap, Files &files);
  void Render(int i, Files &files); //Pre-game renderer for credits and story stuff.
  void UpdateWindowTitle(int score, int fps);
  SDL_Renderer *sdl_renderer;
  
  
 private:
  SDL_Window *sdl_window;
  
  const std::size_t top_bar_height; 
  const std::size_t top_bar_width;
  const std::size_t game_width; 
  const std::size_t game_height;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  
};

#endif