#ifndef LevelMap_H
#define LevelMap_H

#include <iostream>
#include <vector>

class LevelMap {
 public:
  LevelMap():grid_width(0), grid_height(0), screen_width(0),
      screen_height(0), offset(0), level_images_ref({{}}),
      cell_width(0), cell_height(0){};
  
  LevelMap(std::size_t grid_width, std::size_t grid_height, 
      std::size_t screen_width, std::size_t screen_height,
      std::vector<size_t> offset);
  
  int getGridImage(int i, int j); //returns the image reference at i,j index.
  std::vector<float> getXY(int i, int j); //returns the actual coordinates at i,j index.
  void loadMap(std::vector<std::vector<int>> levelgrid); //load a level map from file.
  
  std::size_t cell_height;
  std::size_t cell_width;
  std::vector<size_t> getOffset();
  
 private:  
  //Map variables
  std::vector<std::vector<int>> level_images_ref; //Contains resource references by number;
  std::size_t grid_width;
  std::size_t grid_height;
  std::size_t screen_width;
  std::size_t screen_height;
  std::vector<std::size_t> offset;
};

#endif