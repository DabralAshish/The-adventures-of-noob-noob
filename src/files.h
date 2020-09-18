#ifndef FILES_H
#define FILES_H

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Files{

  public:
    Files(std::string const res_path);
    std::vector<std::vector<int>> getLevelMap(std::string path);  
    std::vector<std::vector<int>> readLevelMap(std::string path);
    
    std::map<std::string, SDL_Texture * > textures;
    SDL_Renderer * sdl_renderer;
    void readAllImages();  
  
  private:  
    std::string const res_path;
};

#endif