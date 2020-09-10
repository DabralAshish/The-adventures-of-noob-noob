#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t top_bar_height, const std::size_t top_bar_width,
                   const std::size_t game_width, const std::size_t game_height,
                   const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : top_bar_height(top_bar_height),
      top_bar_width(top_bar_width),      
      game_width(game_width),
      game_height(game_height),
      screen_width(game_width),
      screen_height(game_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("The-adventures-of-noob-noob", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, game_width,
                                game_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(NoobNoob const noobnoob, SDL_Point const &artefact) {
  SDL_Rect top_bar;
  top_bar.x = 0;
  top_bar.y = 0;
  top_bar.w = top_bar_width;
  top_bar.h = top_bar_height;
  
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  // Render artefact
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = artefact.x * block.w;
  block.y = artefact.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render noobnoob's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : noobnoob.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render noobnoob's head
  block.x = static_cast<int>(noobnoob.head_x) * block.w;
  block.y = static_cast<int>(noobnoob.head_y) * block.h;
  if (noobnoob.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
  
  // Render top bar on top of everything.
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &top_bar);
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"NoobNoob Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
