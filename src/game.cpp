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
  noobnoob.head_x = 17;
  noobnoob.head_y = 31;
  egp = levelmap.getEmptyGridPoints(); //Get all empty spaces where noobnoob can move.
  
  rng = std::mt19937(rd()); 
  uni = std::uniform_int_distribution<int>(0, egp.size()-1);
        
  readArtefacts(); //Should be called only once.
  //placeCoins(); // Randomly place coins.
//   checkArtefacts();//Can be called multiple times.
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
    
    if(noobnoob.enable_story){
      renderer.Render(1, files);
    }else if(noobnoob.enable_noobnoob){
      renderer.Render(noobnoob, artefacts, levelmap, files);
    }else if(endgame){
      renderer.Render(2, files);
    }
    else{
      renderer.Render(0, files);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(frame_count);
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

void Game::processArtefacts(){
  //Always maintain a constant number of coins by keeping track of
  //available coins. Check if noobnoob reached one of the coins
  //positions and remove that coin. 
  
  //Random number (index) generation. 
  
  
  int no_coins = 30; //Get 5 different coins for 5 different places.
  
  bool is_close = false; //Check if an artefact is close. For hinting purposes.
  
  //Count how many coins are left in the artefacts center.
  int count = 0;
//   std::cout <<"------------------------------------------------" << std::endl;
  
  std::string delim = "_";
  
  for(auto const &art : artefacts){
    auto imref = art.first.substr(0, art.first.find(delim));
//     std::cout << "key " << art.first << std::endl;
    if(stoi(imref)==13){ //If 
      count ++; //count all coins.
    }
      
    //Check if noobnoob in the previous step reached a coin.
    //Erase that coin from the artefacts list. count is not increased
    //in this case to account for the now collected coin.
    auto xy = levelmap.getXY(noobnoob.head_x, noobnoob.head_y);
//     std::cout << " noob : " << xy[0] << "," << xy[1] << "  art : " << art.second.x << "," << art.second.y << std::endl;
    if(art.second.x == xy[0] && art.second.y == xy[1]){
      is_close = true;
//       std::cout << "At artefact location " << std::endl;
      //Get the index of the artefact.
      std::vector<int>::const_iterator  itr = std::find(artefact_vals.begin(), artefact_vals.end(), stoi(imref));
      int index = std::distance(artefact_vals.begin(), itr);
//       std::cout << "Artefact is : " << imref << std::endl;
      if(artefact_collect_states[index] == 1){ //Check if the artefact has a collectible state.
//         std::cout << "Artefact collect status is " << 1 << std::endl;
        //Check for collection and update rendering variables.
        if(stoi(imref)==5){
          noobnoob.is_buddha = true;
        }else if(stoi(imref)==12){
          noobnoob.is_soup = true;
          endgame = true;
          noobnoob.enable_noobnoob = false;
          noobnoob.enable_story = false;
        }
        artefacts.erase(art.first); //Collectibles needs to be deleted.
        if(stoi(imref)==13){
//           std::cout << "Coin has been collected " << std::endl;
          count--; //If a coin has been collected, decrease count.
          noobnoob.nc += 1; //Coin collected, increase nc.
        }
        //noobnoob.is_accessible = false;
      }
    }else if( abs(art.second.x - xy[0]) + abs(art.second.y - xy[1]) == 20){
      is_close = true;
//       std::cout << "----------------"<<std::endl;
//       std::cout << "x " << art.second.x << " --- "<< xy[0] << std::endl;
//       std::cout << "y " << art.second.y << " --- "<< xy[1] << std::endl;
      std::vector<int>::iterator it = std::find(noobnoob.artefact_vals.begin(), noobnoob.artefact_vals.end(), stoi(imref));
      int index = std::distance(noobnoob.artefact_vals.begin(), it);
//       std::cout << " found imref " << imref << " is_accessible " << noobnoob.is_accessible << std::endl;
      if(stoi(imref)==4){
        noobnoob.hint.assign("Hint : Press E to payoff the guard");
        if(noobnoob.is_accessible){
          noobnoob.nc = noobnoob.nc -3;
          artefacts.erase(art.first);
//           noobnoob.is_accessible=false;
//           std::cout <<noobnoob.artefact_pass_states[index] << std::endl;
          noobnoob.artefact_pass_states[index] = 1;
//           std::cout << "noobnoob : " << noobnoob.artefact_pass_states[index] << " , " << imref << std::endl;
        }  
      }else if(stoi(imref)==9){
        noobnoob.hint.assign("Hint : Press E to rotate the wheel");
        if(noobnoob.is_accessible){
          is_discard = true;
//           noobnoob.is_accessible = false;
        }
        //Redistribute some coins.
      }else if(stoi(imref)==6){
        noobnoob.hint.assign("Hint : Press E to go, R to come back");
        if(noobnoob.is_accessible){
          if(!noobnoob.is_transported){ //If it is already transported, bring it back to well.
            //Transport it somewhere randomly.
            if(noobnoob.nc > 20){ //If 30 coins have been collected. Tranport to key!
              noobnoob.head_x = 28;
              noobnoob.head_y = 7;
            }else{
              bool found = false;
              int egpi = uni(rng); //Get a random index from egp(empty spaces).
//               std::cout << " random index " << egpi << std::endl;
              while(!found){ //Check all possible empty places.
                std::vector<int>::iterator ite = std::find(current_coins.begin(), current_coins.end(), egpi);
                int index = std::distance(current_coins.begin(), ite);
//                 std::cout << "found in current_coins : " << index <<std::endl;
                if(ite == current_coins.end()){ // The current point doesn't contain a coin, put noobnoob here now.
//                   std::cout << " found match " << egpi << std::endl;
                  noobnoob.head_x = egp[egpi][1];
                  noobnoob.head_y = egp[egpi][0];
//                   std::cout << " transport to : " << noobnoob.head_x << ", " << noobnoob.head_y << std::endl;
                  found = true;
                }
              }
            }
            noobnoob.is_transported = true;
          }
        }
        
      }else if(stoi(imref)==7){
        noobnoob.hint.assign("Hint : Press E to collect key");
        if(noobnoob.is_accessible){
          artefacts.erase(art.first);
          noobnoob.is_key = true;
        }  
        
      }else if(stoi(imref)==14){
        noobnoob.hint.assign("Hint : Press E, Need both artefacts!");
        if(noobnoob.is_accessible){
          if(noobnoob.is_key && noobnoob.is_buddha){
            artefacts.erase(art.first);
            noobnoob.artefact_pass_states[index] = 1;
            noobnoob.artefact_collect_states[index] = 1;
          }
          noobnoob.is_accessible = false;
        }  
      }
    }
  }
  
  if(noobnoob.is_transported){ //If noobnoob was previously transported, bring it back.
    if(noobnoob.is_return){
      std::cout << "Bringing back " << std::endl;
      noobnoob.head_x = 15;
      noobnoob.head_y = 31;
      noobnoob.nc = noobnoob.nc -1; //Transportation cost. 1 coin.
      noobnoob.is_return = false;
      noobnoob.is_transported = false;
    }
  }
  
  noobnoob.is_accessible = false; //overall deactivate accessibility.
  
  //Reset the hint, if noobnoob is not close to any artefact (coins not considered).
  if(!is_close)
    noobnoob.hint.assign(" ");
  
//   std::cout << " Found coins  : " << count << std::endl;
//   std::cout << " Adding coins : " << no_coins-count << std::endl;
//   std::cout << "egp size " << egp.size() << std::endl;
  
  if(is_discard){
    for (auto it = artefacts.cbegin(); it != artefacts.cend(); ){
      auto k = it->first;
      auto imref = k.substr(0, k.find(delim));
      if(stoi(imref)==13)
      {
        it = artefacts.erase(it);
//         std::cout << "deleting coin" << std::endl;
      }else{
        it++;
      }
    }
    current_coins.clear();
//     std::cout << " cc size " << current_coins.size() << std::endl;
    count = 0;
    is_discard = false;
  }
  
  //Find the required no. of coins (no_coins - count) and add them to artefacts.
  int i = 0;
  while(i < no_coins - count){
//     std::cout << "---------------coining-------------" << std::endl;
    int r = uni(rng); //Generate random indices for egp.
//     std::cout << "egp " << egp.size() << "   Got index " << r << "  coins : " << no_coins-count << std::endl;
//     std::cout << egp[egp.size()-1][0] << " , " << egp[egp.size()-1][1] << std::endl;
    //Check if the vector of grid points containing coins was generated earlier or not, add accordingly.
    if(current_coins.size()==0){
//       std::cout << "Current size 0 case " << std::endl;
      //Add the first random index for coin to current_coins.
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
//         std::cout << "Added coin " << i << std::endl;
      }
      
    }else{
//       std::cout << "Current size non-zero " << std::endl;
      //find if the randomly generated index (r) is present in the currently existing coin set.
      //if no, then use the index and put a coin at the corresponding location.
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
//           std::cout << "Added coin " << i << std::endl;
        }
      }
    }
  }
  
//   std::cout << " current coins : " << current_coins.size() << std::endl;
}

void Game::readArtefacts(){
  noobnoob.artefact_pass_states = artefact_pass_states;
  noobnoob.artefact_collect_states = artefact_collect_states;
  noobnoob.artefact_vals = artefact_vals;
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
    if(v[2]!=0){ //don't add SDL_Rect for 0 (wall).
      std::string s =  std::to_string(v[2]) + "_" + std::to_string(v[0]) +"_"+ std::to_string( v[1]);
      artefacts.insert( std::make_pair(s , sr) );  //We need this for textures.
    }
  }
}



void Game::Update() { 
  //Update noobnoob
  noobnoob.Update();
  processArtefacts();
}

int Game::GetSize() const { return noobnoob.size; }