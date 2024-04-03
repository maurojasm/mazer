#include "../include/tile.h"
#include "../include/utils.h"

Tile::Tile(int x, int y, int t_type) {
    // set position
    hit_box.x = x;
    hit_box.y = y;

    // set tile dimension
    hit_box.w = TILE_WIDTH;
    hit_box.h = TILE_HEIGHT;

    // set type
    tile_type = t_type;
}

void Tile::render(SDL_Rect& camera, Texture& tile_texture, 
                    SDL_Rect tile_sprites[], SDL_Renderer* renderer) {
    if (check_collision(camera, hit_box)) {
        tile_texture.render(hit_box.x - camera.x, hit_box.y - camera.y, renderer, &tile_sprites[tile_type]);
    }
}