#include <iostream>
#include "controller.h"
#include "files.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kTopBarHeight{40};
  constexpr std::size_t kTopBarWidth{640};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGameWidth{640};
  constexpr std::size_t kGameHeight{680}; //sum of Top bar and screen height.
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  std::string const res_path = "../resources";
  
  Renderer renderer(kTopBarHeight, kTopBarWidth, kGameWidth, kGameHeight, 
                    kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, kScreenWidth, kScreenHeight, std::vector<size_t> {0, kTopBarHeight}, res_path);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}