#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

#include "texture.h"

class Tile {
    public:
        // constructor
        // initializes position and tile type
        Tile(int x, int y, int t_type);

        // render tile to screen
        void render(SDL_Rect& camera, Texture& tile_texture, 
                    SDL_Rect tile_sprites[], SDL_Renderer* renderer);

        /* getter funcs */ 
        
        // get tile type
        int get_type() {return tile_type;}

        // get tile hit box
        SDL_Rect get_hit_box() {return hit_box;}
        
        int get_width() {return TILE_WIDTH;}
        int get_height() {return TILE_HEIGHT;}
    private:
        // tile constants
		const int TILE_WIDTH = 80;
		const int TILE_HEIGHT = 80;

        // tile hit box
        SDL_Rect hit_box;

        // title type
        int tile_type;
};