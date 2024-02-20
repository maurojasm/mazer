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
        
        //Starts up SDL and creates window
        bool init();

        //Frees media and shuts down SDL
        void close();

        //The window we'll be rendering to
        SDL_Window* window = NULL;

        //The window renderer
        SDL_Renderer* renderer = NULL;

        //Scene textures
        Texture dot_texture;
        Texture tile_texture;
};