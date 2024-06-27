#include "../include/bullet.h"

Bullet::Bullet(int x, int y, Direction dir, int w, int h) {
    hit_box.x = x; hit_box.y = y;
    b_dir = dir;
    b_width = w; b_height = h;
    hit_box.w = w; hit_box.h = h;
    b_vel = 5; vel_x = 0; vel_y = 0;
}

bool Bullet::collision(int screen_w, int screen_h, vector<Tile*> game_tiles) {
    if ((hit_box.x < 0) || (hit_box.x + b_width > screen_w)) {
        return true;
    }
    if ((hit_box.y < 0) || (hit_box.y + b_height > screen_h)) {
        return true;
    }
    if (touches_wall(game_tiles)) {
        return true;
    }
    return false;
}

bool Bullet::touches_wall(vector<Tile*> game_tiles) {
    for (unsigned i = 0; i < game_tiles.size(); i++) {
        // from all tiles, check only the ones that are wall type
        if (game_tiles[i]->get_type() == 1) {
            // check if collision occurs
            if (check_collision(hit_box, game_tiles[i]->get_hit_box())) {
                return true;
            }
        }
    }
    return false;
}

void Bullet::render(Texture* texture, SDL_Renderer* renderer, SDL_Rect& camera) {
    // quad to render to, location relative to camera
    SDL_Rect renderQuad{ (hit_box.x - camera.x), (hit_box.y - camera.y), b_width, b_height };
    // render texture
    texture->render((hit_box.x - camera.x), (hit_box.y - camera.y), renderer, NULL, &renderQuad);
}

void Bullet::move(int screen_w, int screen_h) {
    // move bullet based on direction given
    switch (b_dir) {
    case UP_DIR:
        hit_box.y -= b_vel;
        break;
    case DOWN_DIR:
        hit_box.y += b_vel;
        break;
    case LEFT_DIR:
        hit_box.x -= b_vel;
        break;
    case RIGHT_DIR:
        hit_box.x += b_vel;
        break;
    }
}