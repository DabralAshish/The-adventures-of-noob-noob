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

void LevelMap::loadMap(int level){
  //This should be replaced by proper map later!
  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_int_distribution<> dist(1, 6);
  
  for(int i=0; i < grid_height; i++){
    std::vector<int> row; //row vector
    for(int j=0; j< grid_width; j++){
      row.push_back(dist(eng));
    }
    level_images_ref.push_back(row); //add row vector to level map
  }
}

int LevelMap::getGridImage(int i, int j){
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