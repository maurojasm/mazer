#include "../include/dot.h"
#include "../include/texture.h"
#include "../include/utils.h"

Dot::Dot() {
    // initialize hit box dimentions
    hit_box.x = 0;
    hit_box.y = 160;
    hit_box.h = d_height;
    hit_box.w = d_width;

    // initialize dot's velocity
    x_vel = 0;
    y_vel = 0;
}

void Dot::handle_event(SDL_Event& e) {
    // if key was pressed add velocity
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        // adjust the velocity
        switch (e.key.keysym.sym) {
        case SDLK_UP: y_vel -= max_vel; break;
        case SDLK_DOWN: y_vel += max_vel; break;
        case SDLK_LEFT: x_vel -= max_vel; break;
        case SDLK_RIGHT: x_vel += max_vel; break;
        }
    }
    // if key was released remove velocity
    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        // adjust the velocity
        switch (e.key.keysym.sym) {
        case SDLK_UP: y_vel += max_vel; break;
        case SDLK_DOWN: y_vel -= max_vel; break;
        case SDLK_LEFT: x_vel += max_vel; break;
        case SDLK_RIGHT: x_vel -= max_vel; break;
        }
    }
}

void Dot::move(int LEVEL_HEIGHT, int LEVEL_WIDTH, int TOTAL_TILES, std::vector<Tile*> game_tiles) {
    // move dot left or right
    hit_box.x += x_vel;

    // check screen bounds or touches wall
    if (hit_box.x < 0 || hit_box.x + d_width > LEVEL_WIDTH || touches_wall(game_tiles, TOTAL_TILES)) {
        // move back
        hit_box.x -= x_vel;
    }

    // move dot up or down
    hit_box.y += y_vel;

    // check screen bounds or touches wall
    if (hit_box.y < 0 || hit_box.y + d_height > LEVEL_HEIGHT || touches_wall(game_tiles, TOTAL_TILES)) {
        // move back
        hit_box.y -= y_vel;
    }

}

void Dot::render(Texture& dot_texture, SDL_Rect& camera, SDL_Renderer* renderer) {
    // render dot with texture
    SDL_Rect renderQuad = {
        hit_box.x - camera.x,
        hit_box.y - camera.y,
        hit_box.w,
        hit_box.h
    };
    dot_texture.render(hit_box.x - camera.x, hit_box.y - camera.y, renderer, NULL, &renderQuad);
}

void Dot::set_camera(SDL_Rect& camera, int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_WIDTH, int LEVEL_HEIGHT) {
    //Center the camera over the dot
    camera.x = (hit_box.x + d_width / 2) - SCREEN_WIDTH / 2;
    camera.y = (hit_box.y + d_height / 2) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if (camera.x < 0) { camera.x = 0; }
    if (camera.y < 0) { camera.y = 0; }
    if (camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

bool Dot::touches_wall(std::vector<Tile*> game_tiles, int TOTAL_TILES) {
    // check all tiles
    for (int i = 0; i < TOTAL_TILES; i++) {
        // if tile is a wall type
        if (game_tiles[i]->get_type() == 1) {
            // check collison between dot's hit box and the wall tile
            if (check_collision(hit_box, game_tiles[i]->get_hit_box())) {
                return true;
            }
        }
    }
    return false;
}

bool Dot::check_win(int LEVEL_WIDTH, int LEVEL_HEIGHT) {
    // check if player is in the "win zone"
    if ((hit_box.x > LEVEL_WIDTH - 40) && (hit_box.y > LEVEL_HEIGHT - 320)) {
        return true;
    }
    return false;
}

void Dot::reset_location() {
    hit_box.x = 0;
    hit_box.y = 160;
}