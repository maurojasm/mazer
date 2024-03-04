#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
// #include <SDL.h>
// #include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "../include/dot.h"
#include "../include/texture.h"

Dot::Dot() {
    // initialize hit box dimentions
    hit_box.x = 0;
    hit_box.y = 0;
    hit_box.h = d_height;

    // initialize dot's velocity
    x_vel = 0;
    y_vel = 0;
}

void Dot::render(Texture &dot_texture, SDL_Renderer *renderer) {
    // render dot with texture
    
}