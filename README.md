# CPPND: Udacity Capstone Game: The adventures of NoobNoob

Project description:
The adventures of NoobNoob is a puzzle game build for [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) as the final capstone project. The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses. Even though this game was inspired by the SNAKE game template, it has been highly modified to provide the current game play.

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


## How to play
1. Use up/down/left/right arrows for movement.
2. Read instructions on the screen.

## Rubric points addressed
1. Compiling and testing:
  - Additional librariries required for building are listed (the instructions worked for building the game on the udacity platform).
  - The project used cmake and make to compile as requested.

2. Object-oriented programming:
  - The project is clearly divided into classes demonstrating the use of object oriented programming:
     - The main class initializes the game variables: game.cpp (for main game loop), renderer.cpp (for rendering the graphics), levelmap.cpp
       (used for dealing with level map functionalities such as finding exact x,y location of images on the map. 
  - noobnoob.cpp (the main player of the game has been defined separately and contains player info and controls movement across the grids 
    through function UpateNoobNoob() (Line 12). Various attributes of the player (noobnoob.h, Line 39-50) has been defined. These control
    the interaction of the player with game objects.
  - files.cpp (for loading all images and levelmap files from disk). 
  - Controller.cpp detects all user inputs based on key presses and converts them into useful game moves.
  
3.  Loops, Functions, I/O:
  - Functions and loops have been used heavily for providing the game functionalities.
  - The main function initializes the game and creates required instances: (main.cpp) Line 21, 23, 24.
  - The project demonstrates and understanding of constrol structures in game.cpp (Line 42) which executes the main game loop.
  - Looping in a filestream (files.cpp, Line 10, 33)and loading images using advanced SDL functions (Line 50) have been shown.
  - All images were loaded and converted to textures beforehand so that overhead during rendering is used.
  - Use of advanced data structures such as map<> (files.h, line 19) is done to access resources such as textures to be called 
    easily in renderer (renderer.cpp, Line 203-209, where all textures stored in the map are called by a key).
  - Controller.cpp contains switch statements to accept movement keystrokes and sets other bool variables (Line 35-55) that are used to detect
    position, interact and activate artefacts. Example, variables such as enable_story allow a splash window with instructions and some story.
    This is used to activate a different temporary renderer (Line 60) to display pre-game and post game screens.
  - The most sophisticated function is Game::processArtefacts(). The function is executed after the player makes a movement (Line 332) and 
    performs wide variety of actions. 
      - Line 101, a for each loop is used to iterate over a map of artefacts.
      - Then the position of the player is checked (Line 113).
      - To provide interactivity with non-overlapping artefacts, vicinity check is done (Line 139).
      - Note that the not all artefacts are constant. Coins are generated, collected and redistributed throughout. This requires a highly
        sophisticated loop especially depending on the kind of artefact used(collectible/non-collectibles). The numbers in if-comparisons
        correspond to artefacts. Example, 5 means buddha, 7 means a key, 13 means a coin and so on. In addition, state vectors for these
        artefacts have been used which allow us a finer control on the current state of the artefacts (Line 31-33, game.h).
      - Random number generation (Line 255, 302, game.cpp) is used to assign coins to different empty spots which are again dyanmic due 
        to player movement. All the coins are put into the dictionary along with other artefacts so that similar interactivity rules can
        be applied for vicinity and state detection and manipulation.
   - Overall, the project demonstrates a the use of a wide variety of concepts.
      

The project demonstrates an understanding of C++ functions and control structures.
Game.cpp, line 267
The project uses Object Oriented Programming techniques.
GameObjects.h
Classes use appropriate access specifiers for class members.
GameObjects.h
Classes abstract implementation details from their interfaces.
Game.h
The project follows the Rule of 5.
GameObjects.h line 36-40
The project uses smart pointers instead of raw pointers.
Game.h line 46-48
The project uses multithreading.
Timer.cpp line 34
A mutex or lock is used in the project.
Timer.cpp line 20
