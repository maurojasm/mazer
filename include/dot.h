// #ifdef DOT_PLAYER
// #define DOT_PLAYER
#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
// #include <SDL.h>
// #include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "texture.h"

class Dot {
    public:
        // constructor
        Dot();

        // handles key press events to ajust dot's vel
        // void handle_event(SDL_Event &e);

        // render dot to the screen
        void render(Texture &dot_texture, SDL_Rect& camera, SDL_Renderer *renderer);

        // handle key presses to adjust velocity
        void handle_event(SDL_Event& e);

        // move the dot
        void move(int LEVEL_HEIGHT, int LEVEL_WIDTH);

        // set camera over the dot
        void set_camera(SDL_Rect& camera, int SCREEN_WIDTH, 
                        int SCREEN_HEIGHT, int LEVEL_WIDTH, 
                        int LEVEL_HEIGHT);

    private:
        // dot dimensions
        static const int d_height = 20;
        static const int d_width = 20;

        // max dot velocity
        static const int max_vel = 10;

        // dot's collision box
        SDL_Rect hit_box;

        // velocity of the dot
        int x_vel, y_vel;
};

// #endif