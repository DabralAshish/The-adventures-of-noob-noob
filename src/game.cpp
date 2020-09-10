#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, 
           std::size_t screen_width, std::size_t screen_height)
    : noobnoob(grid_width, grid_height, screen_width, screen_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceArtefact();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, noobnoob);
    Update();
    renderer.Render(noobnoob, artefact);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceArtefact() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a noobnoob item before placing
    // artefact.
    if (!noobnoob.NoobNoobCell(x, y)) {
      artefact.x = x;
      artefact.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!noobnoob.alive) return;

  noobnoob.Update();

  int new_x = static_cast<int>(noobnoob.head_x);
  int new_y = static_cast<int>(noobnoob.head_y);

  // Check if there's food over here
  if (artefact.x == new_x && artefact.y == new_y) {
    score++;
    PlaceArtefact();
    // Grow noobnoob and increase speed.
    //noobnoob.GrowBody();
    //noobnoob.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return noobnoob.size; }