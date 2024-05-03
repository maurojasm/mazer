#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "texture.h"

class Tile {
public:
    /*
    Class constructor - sets position and type of tile.

    @param x        x-coordinate position
    @param y        y-coordinate position
    @param t_type   0 walkable path, 1 wall
    */
    Tile(int x, int y, int t_type);

    /*
    Renders tile to screen.

    @param camera       camera used to check if tile is inside
    @param tile_texture texture to render the tile to
    @param tile_sprites array of tile sprites
    @param renderer     renderer used to render the texture
    */
    void render(SDL_Rect& camera, Texture& tile_texture, SDL_Rect tile_sprites[], SDL_Renderer* renderer);

    /* ---- Getter functions ---- */

    SDL_Rect get_hit_box() { return hit_box; }
    int get_type() { return tile_type; }
    int get_width() { return TILE_WIDTH; }
    int get_height() { return TILE_HEIGHT; }

    /* -------------------------- */
private:
    // tile constants
    const int TILE_WIDTH = 80;
    const int TILE_HEIGHT = 80;

    // tile hit box
    SDL_Rect hit_box;

    // title type
    int tile_type;
};

#endif