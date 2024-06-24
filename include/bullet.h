#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

#include "texture.h"
#include "utils.h"
#include "tile.h"
#include <vector>

using std::vector;

class Bullet {
public:
    Bullet(int x, int y, Direction dir, int w = 10, int h = 10);
    bool collision(int level_w, int level_h, vector<Tile*> game_tiles);
    void render(Texture* texture, SDL_Renderer* renderer, SDL_Rect& camera);
    void move(int screen_w, int screen_h);
    bool touches_wall(vector<Tile*> game_tiles);
private:
    // int b_x, b_y;
    int b_width, b_height;
    int b_vel, vel_x, vel_y;
    // int damage;
    SDL_Rect hit_box;

    Direction b_dir;
};

#endif