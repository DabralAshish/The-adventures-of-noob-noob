#include <iostream>
#include <random>
#include <levelmap.h>

LevelMap::LevelMap(std::size_t grid_width, std::size_t grid_height, 
         std::size_t screen_width, std::size_t screen_height,
         std::vector<std::size_t> offset)
   : grid_width(grid_width), grid_height(grid_height), 
     screen_width(screen_width),screen_height(screen_height),
     cell_height(screen_height/grid_height), cell_width(screen_width/grid_width), 
     offset(offset){
}

void LevelMap::loadMap(std::vector<std::vector<int>> levelgrid){
    level_images_ref = levelgrid;
}

int LevelMap::getGridImage(int i, int j){
  std::cout << " x : " << i << "   y : " << j << std::endl;
  std::cout << level_images_ref[i][j] << std::endl;
  return level_images_ref[i][j];   
}

std::vector<float> LevelMap::getXY(int i, int j){
  std::vector<float> xy;
  xy.push_back( cell_width  * i  + offset[0] ); //add x offset
  xy.push_back( cell_height * j  + offset[1] ); //add y offset
    
  return xy;
} 

std::vector<size_t> LevelMap::getOffset(){
  return {offset[0]/cell_width, offset[1]/cell_height};
}