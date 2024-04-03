#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
// #include <SDL.h>
// #include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

using std::string;

class Maze_Gen {
    public:
        //constructor
        Maze_Gen();

        // generates random hex maze
        string generate_maze(int size = 5);

    //private:
};