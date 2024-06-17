#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

#include "texture.h"
#include "utils.h"

class Bullet {
public:
    Bullet(int x, int y, Direction dir, int w = 10, int h = 10);
    bool check_collision(int screen_w, int screen_h);
    void render(Texture* texture, SDL_Renderer* renderer);
    void move(int screen_w, int screen_h);
private:
    int b_x, b_y;
    int b_width, b_height;
    int b_vel, vel_x, vel_y;
    // int damage;

    Direction b_dir;
};

#endif