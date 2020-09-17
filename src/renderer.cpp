#include "renderer.h"
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
// #include<SDL2/SDL2.h>
// #include<SDL2/SDL2_image.h>
//#/usr/lib/x86_64-linux-gnu/cmake/SDL2/sdl2-config.cmake
//#for error above : apt-get install libsdl2-image-dev
#include <string>

Renderer::Renderer(const std::size_t top_bar_height, const std::size_t top_bar_width,
                   const std::size_t game_width, const std::size_t game_height,
                   const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : top_bar_height(top_bar_height),
      top_bar_width(top_bar_width),      
      game_width(game_width),
      game_height(game_height),
      screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height){
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
  
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(NoobNoob const noobnoob, SDL_Point const &artefact, LevelMap levelmap) {
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
  
//   Render level map
//   for(int i = 0; i < grid_width; i++){
//     for(int j = 0; j < grid_height; j++){
//       SDL_Rect rct;
//       auto xy = levelmap.getXY(i, j);
//       rct.x = xy[0];
//       rct.y = xy[1];
//       rct.w = levelmap.cell_width;
//       rct.h = levelmap.cell_height;
      
//       auto imval = levelmap.getGridImage(i, j);
      
//       if(imval <= 3){
//         SDL_SetRenderDrawColor(sdl_renderer, 0x94, 0xdd, 0xFF, 0xFF);
//         SDL_RenderFillRect(sdl_renderer, &rct);
//       }else if(imval == 4){
//         SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
//         SDL_RenderFillRect(sdl_renderer, &rct);
//       }
//       else{
//         SDL_SetRenderDrawColor(sdl_renderer, 0x0d, 0xba, 0x2F, 0xFF);
//         SDL_RenderFillRect(sdl_renderer, &rct);
//       }
//     }
//   }
  
   //Try to render the map image:png
  SDL_Surface* surface = IMG_Load("/home/workspace/The-adventures-of-noob-noob/src/resources/map.png");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);
  if(surface == NULL){
    std::cout << "Null surface!" << std::endl;
  }
  SDL_Rect map_background;
  map_background.x = 0;
  map_background.y = top_bar_width;
  map_background.w = screen_width;
  map_background.h = screen_height;
  SDL_RenderCopy(sdl_renderer, texture, NULL, &map_background);
  
  // Render artefact
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);
  block.x = artefact.x * block.w;
  block.y = (artefact.y) * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render noobnoob : get x,y coordinates from grid coordinates.
  auto noobpos = levelmap.getXY(noobnoob.head_x, noobnoob.head_y);
  
  SDL_Rect noob_block;
  noob_block.x = noobpos[0];
  noob_block.y = noobpos[1];
  noob_block.w = levelmap.cell_width;
  noob_block.h = levelmap.cell_height;
  //std::cout << " noob " << noob_block.w << ", " << noob_block.h << "\n";

  if (noobnoob.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &noob_block);
  
  // Render top bar on top of everything.
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0x00);
  SDL_RenderFillRect(sdl_renderer, &top_bar);
  
  SDL_DestroyTexture(texture);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"NoobNoob Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
