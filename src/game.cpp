#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, 
           std::size_t screen_width, std::size_t screen_height,
          std::vector<size_t> offset, std::string const res_path)
    : noobnoob(grid_width, grid_height, screen_width, screen_height),
      levelmap(grid_width, grid_height, screen_width, screen_height, offset),
      files(res_path){
  
  levelmap.loadMap(files.readLevelMap("level0"));
  //Noobnoob needs access to map layout.
  noobnoob.levelmap = levelmap;
  noobnoob.head_x = 15;
  noobnoob.head_y = 31;
  egp = levelmap.getEmptyGridPoints();
  readArtefacts(); //Should be called only once.
  placeCoins(); // Randomly place coins.
  checkArtefacts();//Can be called multiple times.
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  files.sdl_renderer = renderer.sdl_renderer;
  files.readAllImages();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, noobnoob);
    Update();
    renderer.Render(noobnoob, artefacts, levelmap, files);

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

void Game::placeCoins(){
  //Alwasy maintain a constant number of coins by keeping track of
  //available coins. Check if noobnoob reached one of the coins
  //positions and remove that coin. 
  
  int no_coins = 30; //Get 5 different coins for 5 different places.
  
  //Count how many coins are left in the artefacts center.
  int count = 0;
//   std::cout <<"------------------------------------------------" << std::endl;
  for(auto const &art : artefacts){
    std::string delim = "_";
    auto imref = art.first.substr(0, art.first.find(delim));
    if(stoi(imref)==13){ //If 
      count ++; //count all coins.
    }
    
    //Check if noobnoob in the previous step reached a coin.
    //Erase that coin from the artefacts list. count is not increased
    //in this case to account for the now collected coin.
    auto xy = levelmap.getXY(noobnoob.head_x, noobnoob.head_y);
//     std::cout << " noob : " << xy[0] << "," << xy[1] << "  art : " << art.second.x << "," << art.second.y << std::endl;
    if(art.second.x == xy[0] && art.second.y == xy[1]){
//       std::cout << "At artefact location " << std::endl;
      //Get the index of the artefact.
      std::vector<int>::const_iterator  itr = std::find(artefact_vals.begin(), artefact_vals.end(), stoi(imref));
      int index = std::distance(artefact_vals.begin(), itr);
//       std::cout << "Artefact is : " << imref << std::endl;
      if(artefact_collect_states[index] == 1){ //Check if the artefact has a collectible state.
//         std::cout << "Artefact collect status is " << 1 << std::endl;
        //Check for collection and update rendering bools.
        if(stoi(imref)==5){
          noobnoob.is_buddha = true;
        }else if(stoi(imref)==7){
          noobnoob.is_key = true;
        }else if(stoi(imref)==12){
          noobnoob.is_soup = true;
        }
        
        artefacts.erase(art.first); //Collectibles needs to be deleted.
        if(stoi(imref)==13){
//           std::cout << "Coin has been collected " << std::endl;
          count--; //If a coin has been collected, decrease count.
          noobnoob.nc += 1; //Coin collected, increase nc.
        }
      }
    } 
  }
  
  //Random number (index) generation. 
  std::mt19937 rng(rd()); 
  std::uniform_int_distribution<int> uni(0,egp.size());
  
//   std::cout << " Found coins  : " << count << std::endl;
//   std::cout << " Adding coins : " << no_coins-count << std::endl;
//   std::cout << "egp size " << egp.size() << std::endl;
  //Find the required no. of coins (no_coins - count) and add them to artefacts.
  int i = 0;
  while(i < no_coins - count){
    int r = uni(rng); //Generate random indices for egp.
//     std::cout << "Got r " << r << std::endl;
    //Check if the vector was generated earlier or not, add accordingly.
    if(current_coins.size()==0){
//       std::cout << "Current size 0 case " << std::endl;
      current_coins.push_back(r);
      SDL_Rect sr;
      auto v = egp[r];
      if(v[0] != noobnoob.head_x && v[1] != noobnoob.head_y){ //Don't put coins on noobnoob!
        auto xy = levelmap.getXY(v[1], v[0]);
        sr.x = xy[0];
        sr.y = xy[1];
        sr.w = levelmap.cell_width;
        sr.h = levelmap.cell_height;
        std::string s =  std::to_string(13) + "_" + std::to_string(v[0]) +"_"+ std::to_string( v[1]);
        artefacts.insert( std::make_pair(s , sr) );  //We need this for textures.
        i++;
      }
      
    }else{
//       std::cout << "Current size non-zero " << std::endl;
      std::vector<int>::iterator it = std::find(current_coins.begin(), current_coins.end(), r);
      if (it == current_coins.end()){
//         std::cout << "Not adding duplicate " << std::endl;
        current_coins.push_back(r);
        SDL_Rect sr;
        auto v = egp[r];
        if(v[0] != noobnoob.head_x && v[1] != noobnoob.head_y){
          auto xy = levelmap.getXY(v[1], v[0]);
          sr.x = xy[0];
          sr.y = xy[1];
          sr.w = levelmap.cell_width;
          sr.h = levelmap.cell_height;
          std::string s =  std::to_string(13) + "_" + std::to_string(v[0]) +"_"+ std::to_string( v[1]);
          artefacts.insert( std::make_pair(s , sr) );  //We need this for textures.
          i++;
        }
      }
    }
  }
  
//   std::cout << " current coins : " << current_coins.size() << std::endl;
}

void Game::checkArtefacts() {
  //ToDo
  
}

void Game::readArtefacts(){
  //Create a vector of artefacts using SDL_Point that can be rendered by SDL.
  auto indices = levelmap.findVal(artefact_vals);
  for(std::vector<int> v: indices){
//     std::cout << "reading vals : " << v[0] << "," << v[1] << " : " << v[2]<< std::endl;
    SDL_Rect sr;
    auto xy = levelmap.getXY(v[1], v[0]);
    sr.x = xy[0];
    sr.y = xy[1];
    sr.w = levelmap.cell_width;
    sr.h = levelmap.cell_height;
    std::string s =  std::to_string(v[2]) + "_" + std::to_string(v[0]) +"_"+ std::to_string( v[1]);
    artefacts.insert( std::make_pair(s , sr) );  //We need this for textures.
  }
}



void Game::Update() {
  noobnoob.artefact_pass_states = artefact_pass_states;
  noobnoob.artefact_collect_states = artefact_collect_states;
  noobnoob.artefact_vals = artefact_vals;
  
  //Update noobnoob
  noobnoob.Update();
  placeCoins();
  checkArtefacts();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return noobnoob.size; }