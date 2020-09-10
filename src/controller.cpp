#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "noobnoob.h"

void Controller::ChangeDirection(NoobNoob &noobnoob, NoobNoob::Direction input,
                                 NoobNoob::Direction opposite) const {
  if (noobnoob.direction != opposite || noobnoob.size == 1) noobnoob.direction = input;
  return;
}

void Controller::HandleInput(bool &running, NoobNoob &noobnoob) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(noobnoob, NoobNoob::Direction::kUp,
                          NoobNoob::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(noobnoob, NoobNoob::Direction::kDown,
                          NoobNoob::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(noobnoob, NoobNoob::Direction::kLeft,
                          NoobNoob::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(noobnoob, NoobNoob::Direction::kRight,
                          NoobNoob::Direction::kLeft);
          break;
      }
    }
  }
}