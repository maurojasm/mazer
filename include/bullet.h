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
    /*
    Class constructor, creates bullet with given location, direction, and size.

    @param x    x-coordinate hitbox's location
    @param y    y-coordinate hitbox's location
    @param dir  Direction variable of bullet
    @param w    width of bullet's hitbox
    @param h    height of bullet's hitbox
    */
    Bullet(int x, int y, Direction dir, int w = 10, int h = 10);

    /*
    Checks for collision between bullet's hitbox, game tiles, and level dimensions.

    @param level_w      level's width to check for out of bounds conditions
    @param level_h      level's height to check for out of bounds conditions
    @param game_tiles   vector of tile objects to check for collision
    @return             true if collision occurs, false otherwise
    */
    bool collision(int level_w, int level_h, vector<Tile*> game_tiles);

    /*
    Renders bullet based on passed texture, renderer, and relative to camera.

    @param texture  Texture object of Bullet object to render
    @param renderer renderer used to render texture
    @param camera   camera to render in relation to
    */
    void render(Texture* texture, SDL_Renderer* renderer, SDL_Rect& camera);

    /*
    Moves bullet and checks for collisions.

    @param level_w      level's width to check for out of bounds conditions
    @param level_h      level's height to check for out of bounds conditions
    */
    void move(int level_w, int level_h);

    /*
    Checks if bullet collisions with a wall tile.

    @param game_tiles vector of tile objects to check for collision
    */
    bool touches_wall(vector<Tile*> game_tiles);
private:
    // bullet size
    int b_width, b_height;

    // bullet velocity
    int b_vel, vel_x, vel_y;

    // damage of bullet, @todo implement damage
    // int damage;

    // bullet hitbox
    SDL_Rect hit_box;

    // bullet direction
    Direction b_dir;
};

#endif