#include "../include/player.h"

Player::Player(string im_path, SDL_Renderer* renderer, int w, int h, int x, int y) {
    int rgb[] = { 0, 0xFF, 0xFF };
    if (!player_texture.load_from_file(im_path, renderer, true, rgb)) {
        printf("Error loading Player texture. SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    // location
    hit_box.x = x;
    hit_box.y = y;
    //dimensions
    p_width = w; hit_box.w = w;
    p_height = h; hit_box.h = h;
    // max velocity
    p_vel = 10;
    // axis velocity
    vel_x = 0;
    vel_y = 0;
    // set default direction
    dir = RIGHT_DIR;
    // set default frame
    curr_frame = 0; num_frames = 0;
}

void Player::set_vel(int vel) {
    // max and min velocity
    if (vel < 1 || vel > 20) {
        p_vel = 10;
    }
    else {
        p_vel = vel;
    }
}

void Player::set_size(int w, int h) {
    p_width = w; hit_box.w = w;
    p_height = h; hit_box.h = h;
}

void Player::set_pos(int x, int y) {
    hit_box.x = x;
    hit_box.y = y;
}

void Player::set_bullet_texture(Texture* texture) {
    bullet_texture = texture;
}

void Player::handle_event(SDL_Event& e) {
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
        case SDLK_w: vel_y -= p_vel; dir = UP_DIR; break;
        case SDLK_s: vel_y += p_vel; dir = DOWN_DIR; break;
        case SDLK_a: vel_x -= p_vel; dir = LEFT_DIR; break;
        case SDLK_d: vel_x += p_vel; dir = RIGHT_DIR; break;
        case SDLK_SPACE:
            bullets.push_back(Bullet((hit_box.x + p_width), (hit_box.y + 5), dir));
            break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
        case SDLK_w: vel_y += p_vel; break;
        case SDLK_s: vel_y -= p_vel; break;
        case SDLK_a: vel_x += p_vel; break;
        case SDLK_d: vel_x -= p_vel; break;
        }
    }
}

void Player::move(int LEVEL_HEIGHT, int LEVEL_WIDTH, int TOTAL_TILES, vector<Tile*> game_tiles) {
    // move the player in the x direction
    hit_box.x += vel_x;

    // check if player is out of bounds
    if ((hit_box.x < 0) || (hit_box.x + p_width > LEVEL_WIDTH) || touches_wall(game_tiles, TOTAL_TILES)) {
        // move back
        hit_box.x -= vel_x;
    }

    // move player in the y direction
    hit_box.y += vel_y;

    // check if player is out of bounds
    if ((hit_box.y < 0) || (hit_box.y + p_height > LEVEL_HEIGHT) || touches_wall(game_tiles, TOTAL_TILES)) {
        // move back
        hit_box.y -= vel_y;
    }
    // increase frame if movement is present
    if (vel_y != 0 || vel_x != 0) { ++curr_frame; }
    else { curr_frame = 0; }
    // decrease number of time between frames rendered
    if (curr_frame / 4 >= num_frames) { curr_frame = 0; }
    move_bullets(LEVEL_WIDTH, LEVEL_HEIGHT, game_tiles);
}

void Player::move_bullets(int level_w, int level_h, vector<Tile*> game_tiles) {
    for (unsigned i = 0; i < bullets.size(); i++) {
        bullets[i].move(level_w, level_h);
        if (bullets[i].collision(level_w, level_h, game_tiles)) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

void Player::set_frames(unsigned frames) {
    num_frames = frames;
    int f_width = player_texture.get_width() / frames;
    for (unsigned i = 0; i < frames; i++) {
        SDL_Rect frame = {
            static_cast<int> (i * f_width), // x
            0,                          // y
            f_width,                    // w
            player_texture.get_height()  // h
        };
        frame_clips.push_back(frame);
    }
}

void Player::render(SDL_Renderer* renderer, SDL_Rect& camera) {
    // render texture based on player size
    SDL_Rect clip;
    if (num_frames > 0) {
        clip = frame_clips[curr_frame / 4];
    }
    SDL_Rect renderQuad = { hit_box.x - camera.x, hit_box.y - camera.y, p_width, p_height };
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (dir == RIGHT_DIR) { flip = SDL_FLIP_HORIZONTAL; }

    player_texture.render(hit_box.x - camera.x, hit_box.y - camera.y, renderer, &clip, &renderQuad, 0, NULL, flip);

    for (unsigned i = 0; i < bullets.size(); i++) {
        bullets[i].render(bullet_texture, renderer, camera);
    }
}

void Player::set_camera(SDL_Rect& camera, int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_WIDTH, int LEVEL_HEIGHT) {
    //Center the camera over the dot
    camera.x = (hit_box.x + p_width / 2) - SCREEN_WIDTH / 2;
    camera.y = (hit_box.y + p_height / 2) - SCREEN_HEIGHT / 2;

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

bool Player::touches_wall(std::vector<Tile*> game_tiles, int TOTAL_TILES) {
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

bool Player::check_win(int LEVEL_WIDTH, int LEVEL_HEIGHT) {
    // check if player is in the "win zone"
    if ((hit_box.x > LEVEL_WIDTH - 40) && (hit_box.y > LEVEL_HEIGHT - 320)) {
        return true;
    }
    return false;
}

void Player::reset_location() {
    hit_box.x = 0;
    hit_box.y = 160;
}