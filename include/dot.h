#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
// #include <stdio.h>
#include <string>
#include <vector>

#include "texture.h"
#include "tile.h"

class Dot {
public:
    // constructor
    Dot();

    // render dot to the screen
    void render(Texture& dot_texture, SDL_Rect& camera, SDL_Renderer* renderer);

    // handle key presses to adjust velocity
    void handle_event(SDL_Event& e);

    // move the dot
    void move(int LEVEL_HEIGHT, int LEVEL_WIDTH, int TOTAL_TILES, std::vector<Tile*> game_tiles);

    // set camera over the dot
    void set_camera(SDL_Rect& camera, int SCREEN_WIDTH,
        int SCREEN_HEIGHT, int LEVEL_WIDTH,
        int LEVEL_HEIGHT);

    // checks collision between dot and wall tile
    bool touches_wall(SDL_Rect hit_box, std::vector<Tile*> game_tiles, int TOTAL_TILES);

    bool check_win(int LEVEL_WIDTH, int LEVEL_HEIGHT);

private:
    // dot dimensions (hit box)
    static const int d_height = 20;
    static const int d_width = 20;

    // max dot velocity
    static const int max_vel = 8;

    // dot's collision box
    SDL_Rect hit_box;

    // velocity of the dot
    int x_vel, y_vel;
};

#endif