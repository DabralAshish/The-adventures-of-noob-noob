#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "noobnoob.h"

class Renderer {
 public:
  Renderer(const std::size_t top_bar_height, const std::size_t top_bar_width,
           const std::size_t game_width, const std::size_t game_height,
           const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(NoobNoob const noobnoob, SDL_Point const &artefact);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  
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