#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

class Texture {
    public:
        // constructor
        Texture();

        // destructor
        ~Texture();

        // loads image from specified path
        bool load_from_file(std::string path, SDL_Renderer *renderer);

        // deallocate texture
        void free();

        // set color modulation
        void set_color(Uint8 red, Uint8 green, Uint8 blue);

        // set blending
        void set_blend_mode(SDL_BlendMode blending);

        // set alpha modulation
        void set_alpha(Uint8 alpha);

        // renders texture at given point
        void render(int x, int y, SDL_Renderer* renderer, 
                    SDL_Rect* clip = NULL, double angle = 0.0, 
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Gets image dimensions
        int get_width();
        int get_height();

    private:
        // actual texture
        SDL_Texture *texture;

        // image dimensions
        int t_width, t_height;
};