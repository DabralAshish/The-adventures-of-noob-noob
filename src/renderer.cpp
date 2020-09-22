#include "renderer.h"
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_ttf.h>
// #include<SDL2/SDL2.h>
// #include<SDL2/SDL2_image.h>
//#/usr/lib/x86_64-linux-gnu/cmake/SDL2/sdl2-config.cmake 
//Add flags : -lSDL2_image -lSDL2_ttf to the last line
//#for error above : apt-get install libsdl2-image-dev
//#for fonts : apt-get install libsdl2-ttf-dev
#include <string>
#include "files.h"

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
  
  if(TTF_Init() < 0) {
    std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
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

void Renderer::Render(NoobNoob const noobnoob, std::map<std::string, SDL_Rect> artefacts, LevelMap levelmap, Files &files) {
  // Clear screen
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  // Render top menu bar. 
  SDL_Rect top_bar;
  top_bar.x = 0;
  top_bar.y = 0;
  top_bar.w = top_bar_width;
  top_bar.h = top_bar_height;

  SDL_SetRenderDrawColor(sdl_renderer, 0x34, 0x49, 0x5E, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &top_bar);
  //Fill top menu bar
  SDL_Rect coins;
  coins.x = 10;
  coins.y = 10;
  coins.w = 20;
  coins.h = 20;

  SDL_Texture *cointex = files.textures["13"];
  SDL_RenderCopy(sdl_renderer, cointex, nullptr, &coins);
  
  TTF_Font* txtfont = TTF_OpenFont("../resources/tfont.ttf", 18); 
//   std::cout << SDL_GetError() << std::endl;
  SDL_Color White = {255, 255, 255};
  std::string s = " : " + std::to_string(noobnoob.nc); //Collected coins so far.
  SDL_Surface* msurf = TTF_RenderText_Solid(txtfont, s.c_str() , White); 
  SDL_Texture* message = SDL_CreateTextureFromSurface(sdl_renderer, msurf);
  
  SDL_Rect message_block; 
  message_block.x = 30;  
  message_block.y = 10;  
  message_block.w = msurf->w; 
  message_block.h = msurf->h; 
  
  SDL_FreeSurface(msurf);
  SDL_RenderCopy(sdl_renderer, message, NULL, &message_block);
  
  SDL_Surface* artsurf = TTF_RenderText_Solid(txtfont, "Artefacts : " , White); 
  SDL_Texture* artmess = SDL_CreateTextureFromSurface(sdl_renderer, artsurf);
  
  SDL_Rect artmess_block; 
  artmess_block.x = 100;  
  artmess_block.y = 10;  
  artmess_block.w = artsurf->w; 
  artmess_block.h = artsurf->h; 
  
  SDL_FreeSurface(artsurf);
  SDL_RenderCopy(sdl_renderer, artmess, NULL, &artmess_block);
  
  //Collectibles rendering :
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
  //Try to render the map image:png
  SDL_Rect buddha_block;
  buddha_block.x = 190;
  buddha_block.y = 10;
  buddha_block.w = 20;
  buddha_block.h = 20;
  SDL_Texture *btex = files.textures["5"]; //Buddha
  SDL_RenderFillRect(sdl_renderer, &buddha_block);
  if(noobnoob.is_buddha)
    SDL_RenderCopy(sdl_renderer, btex, nullptr, &buddha_block);
  
  SDL_Rect key_block;
  key_block.x = 220;
  key_block.y = 10;
  key_block.w = 20;
  key_block.h = 20;
  SDL_Texture *ktex = files.textures["7"]; //key
  SDL_RenderFillRect(sdl_renderer, &key_block);
  if(noobnoob.is_key)
    SDL_RenderCopy(sdl_renderer, ktex, nullptr, &key_block);
  
  SDL_Rect soup_block;
  soup_block.x = 250;
  soup_block.y = 10;
  soup_block.w = 20;
  soup_block.h = 20;
  SDL_Texture *stex = files.textures["12"]; //soup
  SDL_RenderFillRect(sdl_renderer, &soup_block);
  if(noobnoob.is_soup)
    SDL_RenderCopy(sdl_renderer, stex, nullptr, &soup_block);
  
  //Create the playable area
  SDL_Rect map_block;
  map_block.x = 0;
  map_block.y = top_bar_height;
  map_block.w = screen_width;
  map_block.h = screen_height;
  
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
  SDL_RenderFillRect(sdl_renderer, &map_block);
  
  //Try to render the map image:png
  SDL_Rect map_background;
  map_background.x = 0;
  map_background.y = top_bar_width;
  map_background.w = screen_width;
  map_background.h = screen_height;
  SDL_Texture *tex = files.textures["map"];
  SDL_RenderCopy(sdl_renderer, tex, nullptr, &map_block);
  
  // Render artefacts
  for(auto const &ent : artefacts){
    auto key = ent.first; //combined key. imageref_x_y
    std::string delim = "_";
    auto imref = key.substr(0, key.find(delim));
    auto destRect = ent.second; //Get actual value of first key.
    SDL_Texture *sptex = files.textures[imref]; //imref is the actual image reference.
    SDL_RenderCopy(sdl_renderer, sptex, nullptr, &destRect);
  }
  
  // Render noobnoob : get x,y coordinates from grid coordinates.
  auto noobpos = levelmap.getXY(noobnoob.head_x, noobnoob.head_y);
//   std::cout << "noob pos : " << noobpos[0] << " , " << noobpos[1] << std::endl;
  
  SDL_Rect noob_block;
  noob_block.x = noobpos[0];
  noob_block.y = noobpos[1];
  noob_block.w = levelmap.cell_width;
  noob_block.h = levelmap.cell_height;
//   std::cout << " noob " << noob_block.x << ", " << noob_block.y << std::endl;
  
  SDL_Texture *pl;
  switch (noobnoob.direction){
    case noobnoob.Direction::kUp:
      pl = files.textures["pl_up"];  
      break;

    case noobnoob.Direction::kDown:
      pl = files.textures["pl_down"];  
      break;

    case noobnoob.Direction::kLeft:
      pl = files.textures["pl_left"];  
      break;

    case noobnoob.Direction::kRight:
      pl = files.textures["pl_right"];  
      break;
  }
  SDL_RenderCopy(sdl_renderer, pl, nullptr, &noob_block);
  
  
  //Show message onscreen
  

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"NoobNoob Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
