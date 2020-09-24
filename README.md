# CPPND: Udacity Capstone Game: The adventures of NoobNoob

The adventures of NoobNoob is puzzle game build for [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) as the final capstone project. The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="noobnoob.png"/>
<img src="noobnoob2.png"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* If the program doesn't compile and gives "IMG_Load reference" errors or ttf errors, do additional things:
  * Note: These installs are temporary on the udacity platform and will dissappear if you log out.
  * Edit : /usr/lib/x86_64-linux-gnu/cmake/SDL2/sdl2-config.cmake and add flags to last line: -lSDL2_image and -lSDL2_ttf
  * Insall the libsdl2 image dev package : apt-get install libsdl2-image-dev
  * Insall the libsdl2 ttf package : apt-get install libsdl2-ttf-dev

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. `cd build`
4. Compile: `cmake .. && make`
5. Run it: `./The-adventures-of-noob-noob`.