#include "noobnoob.h"
#include <cmath>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "levelmap.h"

void NoobNoob::Update() {
  UpateNoobNoob();
}

void NoobNoob::UpateNoobNoob() {
  // Check if direction has changed = movement.
  // Only then make an update.
  if(enable_noobnoob){
  
    if(hasDirectionChanged){
      current = std::chrono::steady_clock::now();
      long diff = std::chrono::duration_cast<std::chrono::milliseconds> (current - last).count();
      //If direction is updated too quickly, for example, if the arrows are kept pressed, the
      //updates might be too quick. Too smoothen it out, only take updates every 200 milliseconds.
      if(diff >= 200){
        float hx = head_x;
          float hy = head_y;

          switch (direction) {
            case Direction::kUp:
              hy -= speed;
              std::cout <<" move up " << "\n";
              break;

            case Direction::kDown:
              hy += speed;
              std::cout <<" move down " << "\n";
              break;

            case Direction::kLeft:
              hx -=speed;
              std::cout <<" move left " << "\n";
              break;

            case Direction::kRight:
              std::cout <<" move right " << "\n";
              hx += speed;
              break;
          }

          //Find what lies in the next cell and move accordingly.
          if( !(hx >= grid_width || hx < 0 || hy >= grid_height || hy < 0) ){
            int r = levelmap.getGridImage(hy, hx); //image ref.

            if( r==1 || r == 8){
              std::cout << "Valid cell to move to : " << hx <<", " << hy << std::endl;
              head_x = hx;
              head_y = hy;
            }else{
              std::vector<int>::iterator it = std::find(artefact_vals.begin(), artefact_vals.end(), r);
              int index = std::distance(artefact_vals.begin(), it);
              //Check the corresponding pass state of that artefact.
              std::cout << "Checking : " << r << " index " << index << "  state " << artefact_pass_states[index] << std::endl;
              if(artefact_pass_states[index]){
                std::cout << "Valid cell to move to : " << hx <<", " << hy << std::endl;
                head_x = hx;
                head_y = hy;
              }else{
                //Do not update since noobnoob is going out of screen.
                std::cout << "Invalid cell to move to : " << hx <<", " << hy << std::endl;
              }
            }
          }

          hasDirectionChanged = false;
          last = std::chrono::steady_clock::now();
          std::cout << "---------------------------------" << std::endl;
        }
      } 
  }
}


// Inefficient method to check if cell is occupied by noobnoob.
bool NoobNoob::NoobNoobCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
 
  return false;
}