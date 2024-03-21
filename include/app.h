#pragma once

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "../include/dot.h"
#include "../include/tile.h"
#include "../include/texture.h"
#include "../include/maze.h"

class App {
    public:
        // constructor
        App();

        // destructor
        ~App();

        // starts application 
        void start();
    private:
        //Screen dimension constants
        const int SCREEN_WIDTH = 640;
        const int SCREEN_HEIGHT = 480;

        //The dimensions of the level
        const int LEVEL_WIDTH = 1600;
        const int LEVEL_HEIGHT = 1600;

        // tile constants
        const int TOTAL_TILES = 192;
		const int TOTAL_TILE_SPRITES = 12;

        //The different tile sprites
		const int TILE_GREEN = 0;
		const int TILE_BLACK = 1;

        //Loads media
        bool load_media();
        
        //Starts up SDL and creates window
        bool init();

        //Frees media and shuts down SDL
        void close();

        // set tiles from maze map
        bool set_tiles();

        //The window we'll be rendering to
        SDL_Window* window = NULL;

        //The window renderer
        SDL_Renderer* renderer = NULL;

        //Scene textures
        Texture dot_texture;
        Texture tile_texture;

        // maze to traverse
        Maze my_maze = Maze(5);
};