#include <iostream>
#include <random>
#include <algorithm>
#include "levelmap.h"

LevelMap::LevelMap(std::size_t grid_width, std::size_t grid_height, 
         std::size_t screen_width, std::size_t screen_height,
         std::vector<std::size_t> offset)
   : grid_width(grid_width), grid_height(grid_height), 
     screen_width(screen_width),screen_height(screen_height),
     cell_height(screen_height/grid_height), cell_width(screen_width/grid_width), 
     offset(offset){
}

void LevelMap::loadMap(std::vector<std::vector<int>> levelgrid){
    levelgrid = levelgrid;
    level_images_ref = levelgrid;
}

int LevelMap::getGridImage(int i, int j){
//   std::cout << " x : " << i << "   y : " << j << std::endl;
//   std::cout << level_images_ref[i][j] << std::endl;
  return level_images_ref[i][j];   
}

std::vector<std::vector<int>> LevelMap::getEmptyGridPoints(){
  std::vector<std::vector<int>> tmp;
  int r = 0;
  
  for(std::vector<int> row: level_images_ref){
    int c = 0;
    for(int gp : row){
      if(gp == 8){ //8 is the empty grid point in the map
        std::vector<int> t = {r, c};
        tmp.push_back(t);
      }
      c++;
    }
    r++;
  }
  
  return std::move(tmp);
}

std::vector<std::vector<int>> LevelMap::findVal(std::vector<int> vals){
  //Every artefact has a number. Find for a given vector of artefact values,
  //the corresponding grid indices. Create a vector of x,y values for each
  //artefact and a return a combined vector for all artefacts.

  std::vector<std::vector<int>> indices;

  int r = 0;
  
  for(std::vector<int> row : level_images_ref){
    //Check each row of the map grid.
    int c = 0;
    for(int val : row){
      //check each element of the row.
      //match each element against the vals vector.
      for(int artval: vals){
        if(val==artval){ //If a match is found, add the current artefact indices.
          std::vector<int> t={r, c, artval}; //create an indices vector.
          indices.push_back(t); //Add to main vector.
        }
      }
      c++; // Another column.
    }
    r++; //Another row.
  }
  
  return indices;
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