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