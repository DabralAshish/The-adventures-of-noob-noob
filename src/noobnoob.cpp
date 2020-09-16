#include "noobnoob.h"
#include <cmath>
#include <iostream>
#include "levelmap.h"

void NoobNoob::Update() {
  UpateNoobNoob();
}

void NoobNoob::UpateNoobNoob() {
  // Check if direction has changed = movement.
  // Only then make an update.
  if(hasDirectionChanged){
    float hx = head_x;
    float hy = head_y;
      
    switch (direction) {
      case Direction::kUp:
        hy -= speed;
        //std::cout <<" move up " << "\n";
        break;

      case Direction::kDown:
        hy += speed;
        //std::cout <<" move down " << "\n";
        break;

      case Direction::kLeft:
        hx -=speed;
        //std::cout <<" move left " << "\n";
        break;

      case Direction::kRight:
        //std::cout <<" move right " << "\n";
        hx += speed;
        break;
    }
    
    if( !(hx >= grid_width || hx < 0 || hy >= grid_height || hy < 0) ){
      if(levelmap.getGridImage(hx, hy) == 4){
        //Do not update since noobnoob is going out of screen.
        std::cout << "Invalid cell to move to : " << hx <<", " << hy << std::endl;
      }else{
        std::cout << "Valid cell to move to : " << hx <<", " << hy << std::endl;
        head_x = hx;
        head_y = hy;
      }
    }
    
    hasDirectionChanged = false;
    std::cout << "---------------------------------" << std::endl;
  }
  
}


// Inefficient method to check if cell is occupied by noobnoob.
bool NoobNoob::NoobNoobCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
 
  return false;
}