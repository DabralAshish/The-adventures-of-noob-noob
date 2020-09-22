#include "files.h"
#include <dirent.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<iostream>
#include<vector>
#include<fstream>


Files::Files(std::string const res_path):res_path(res_path){}

std::vector<std::vector<int>> Files::readLevelMap(std::string path){
  std::vector<std::vector<int>> levelmap;
  std::ifstream myfile (res_path + "/" + path);
  if (myfile) {
    std::string line;
    while (getline(myfile, line)) {
      std::istringstream sline(line);
      int state = 0;
      std::vector<int> tmp;
      while(sline >> state){
        std::cout << state << " ";
        tmp.push_back(int(state));
      }
      std::cout << std::endl;
      levelmap.push_back(tmp);
    }
  }
  return levelmap;
}


void Files::readAllImages(){
  DIR *dir; //Pointer to directory.
  struct dirent *ent; //Struct containing directory information.
  if ((dir = opendir (res_path.c_str())) != NULL) { //Check if directory can be opened.
    while ((ent = readdir (dir)) != NULL) { //Read the directory in a loop and populate ent struct.
      if(ent->d_type == DT_REG){ //Check if the file is a regular file and not a directory.
        std::string fname = ent->d_name; //Read each file/dir information.
        
        std::string ending = ".png"; //png format string for comparison.
        
        size_t lastindex = fname.find_last_of("."); 
        std::string basename = fname.substr(0, lastindex); 
//         std::cout << fname << std::endl;
        //check for specific file format.
        
        if(0 == fname.compare (fname.length() - ending.length(), ending.length(), ending)){
          std::string s = res_path + "/" + fname;                                                                                             
          SDL_Surface* surf = IMG_Load(s.c_str());
          SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surf); //Create texture from surface.
          SDL_FreeSurface(surf); //Free the surface. Not required anymore.
          textures.insert(std::make_pair(basename, texture)); //Poupulate textures dictionary.
//           std::cout << "basename : " << basename << std::endl;
        }
      }
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
  }

}

std::vector<std::vector<int>> Files::getLevelMap(std::string path){
  return readLevelMap(path);
} 