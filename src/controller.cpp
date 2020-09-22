#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "noobnoob.h"


void Controller::HandleInput(bool &running, NoobNoob &noobnoob) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_SPACE){
        std::cout << "space pressed" << std::endl;
        //Only once the initial message has been shown
        //and spacebar is pressed, enable noobnoob.
        noobnoob.enable_story = true;
        noobnoob.count_enables += 1;
        if(noobnoob.count_enables == 2){
          noobnoob.enable_noobnoob = true;
          noobnoob.enable_story = false;
        }
      }
      if(noobnoob.enable_noobnoob){
        noobnoob.hasDirectionChanged = true;
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            noobnoob.direction = NoobNoob::Direction::kUp;
            break;

          case SDLK_DOWN:
            noobnoob.direction = NoobNoob::Direction::kDown;
            break;

          case SDLK_LEFT:
            noobnoob.direction = NoobNoob::Direction::kLeft;
            break;

          case SDLK_RIGHT:
            noobnoob.direction = NoobNoob::Direction::kRight;
            break;
        }
      }
    }
  }
}