#pragma once

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

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

        //default dimensions of the level
        int LEVEL_WIDTH = 1600;
        int LEVEL_HEIGHT = 1600;

        // tile settings
        int TOTAL_TILES = 400;
		static const int TOTAL_TILE_SPRITES = 2;

        // different tile sprites
		const int TILE_GREEN = 0;
		const int TILE_BLACK = 1;

        // default maze dimensions
        int MAZE_DIM = 5;

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
        Maze *my_maze = NULL;

        // tiles required for level
        std::vector<Tile*> game_tiles;

        // sprites from tile texture
        SDL_Rect tile_sprites[TOTAL_TILE_SPRITES];
};