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

void Dot::handle_event(SDL_Event& e) {
    // if key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        // adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: y_vel -= max_vel; break;
            case SDLK_DOWN: y_vel += max_vel; break;
            case SDLK_LEFT: x_vel -= max_vel; break;
            case SDLK_RIGHT: x_vel += max_vel; break;
        }
    }
    // if key was released
    if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        // adjust the velocity
        switch(e.key.keysym.sym) {
            case SDLK_UP: y_vel += max_vel; break;
            case SDLK_DOWN: y_vel -= max_vel; break;
            case SDLK_LEFT: x_vel += max_vel; break;
            case SDLK_RIGHT: x_vel -= max_vel; break;
        }
    }
}

void Dot::move(int LEVEL_HEIGHT, int LEVEL_WIDTH) {
    // move dot left or right
    hit_box.x += x_vel;

    // check screen bounds
    if(hit_box.x < 0 || hit_box.x + d_width > LEVEL_WIDTH) {
        // move back
        hit_box.x -= x_vel;
    }

    // move dot up or down
    hit_box.y += y_vel;

    // check screen bounds
    if(hit_box.y < 0 || hit_box.y + d_height > LEVEL_HEIGHT) {
        // move back
        hit_box.y -= y_vel;
    }

}

void Dot::render(Texture &dot_texture, SDL_Renderer *renderer) {
    // render dot with texture
    dot_texture.render(hit_box.x, hit_box.y, renderer);
}