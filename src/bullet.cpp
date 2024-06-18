#include "../include/bullet.h"

Bullet::Bullet(int x, int y, Direction dir, int w, int h) {
    b_x = x; b_y = y;
    b_dir = dir;
    b_width = w; b_height = h;
    b_vel = 3; vel_x = 0; vel_y = 0;
}

bool Bullet::check_collision(int screen_w, int screen_h) {
    if ((b_x < 0) || (b_x + b_width > screen_w)) {
        return true;
    }
    if ((b_y < 0) || (b_y + b_height > screen_h)) {
        return true;
    }
    return false;
}

void Bullet::render(Texture* texture, SDL_Renderer* renderer, SDL_Rect& camera) {
    SDL_Rect renderQuad{ (b_x - camera.x), (b_y - camera.y), b_width, b_height };
    texture->render((b_x - camera.x), (b_y - camera.y), renderer, NULL, &renderQuad);
}

void Bullet::move(int screen_w, int screen_h) {
    switch (b_dir) {
    case UP_DIR:
        b_y -= b_vel;
        break;
    case DOWN_DIR:
        b_y += b_vel;
        break;
    case LEFT_DIR:
        b_x -= b_vel;
        break;
    case RIGHT_DIR:
        b_x += b_vel;
        break;
    }
    // if ((b_x < 0) || (b_x + b_width > screen_w)) {
    //     if (b_dir == RIGHT_DIR) { b_x -= b_vel; }
    //     else { b_x += b_vel; }
    // }
    // if ((b_y < 0) || (b_y + b_height > screen_h)) {
    //     if (b_dir == DOWN_DIR) { b_y -= b_vel; }
    //     else { b_y += b_vel; }
    // }
}