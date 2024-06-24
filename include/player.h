#ifndef PLAYER_H
#define PLAYER_H

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "texture.h"
#include "bullet.h"
#include "utils.h"
#include "tile.h"

using std::string;
using std::vector;

class Player {
public:

    Player(string im_path, SDL_Renderer* renderer, int w = 20, int h = 20, int x = 0, int y = 0);

    void set_vel(int vel);

    void set_frames(unsigned frames);

    void set_size(int w, int h);

    void set_pos(int x, int y);

    void set_bullet_texture(Texture* texture);

    void handle_event(SDL_Event& e);

    void move(int LEVEL_HEIGHT, int LEVEL_WIDTH, int TOTAL_TILES, std::vector<Tile*> game_tiles);

    /*
    Render dot texture to the screen.

    @param dot_texture  dot's texture to be render
    @param camera use   to determine dot's position of render
    @param renderer     renderer use to render the texture
    */
    void render(SDL_Renderer* renderer, SDL_Rect& camera);

    /*
    Set camera over the dot

    @param camera           camera object
    @param SCREEN_WIDTH     width of the current screen
    @param SCREEN_HEIGHT    height of the current screen
    @param LEVEL_WIDTH      width of the level
    @param LEVEL_HEIGHT     height of the level
    */
    void set_camera(SDL_Rect& camera, int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_WIDTH, int LEVEL_HEIGHT);

    /*
    Checks of Dot is out of screen bounds and wall collisions

    @param game_tiles   list of the level tiles
    @param TOTAL_TILES  total number of level tiles
    @return             true if dot touches a wall
    */
    bool touches_wall(std::vector<Tile*> game_tiles, int TOTAL_TILES);

    /*
    Checks if dot is within bounds to win

    @param LEVEL_WIDTH  width of the level
    @param LEVEL_HEIGHT height of the level
    @return true if player is in "win zone"
    */
    bool check_win(int LEVEL_WIDTH, int LEVEL_HEIGHT);

    /*
    Resets location.
    */
    void reset_location();

private:
    void move_bullets(int screen_w, int screen_h, vector<Tile*> game_tiles);

    // int p_x, p_y;
    int p_width, p_height;
    int p_vel, vel_x, vel_y;

    int curr_frame, num_frames;

    SDL_Rect hit_box;

    Direction dir;

    vector<SDL_Rect> frame_clips;

    Texture player_texture;

    Texture* bullet_texture;

    vector<Bullet> bullets;
};

#endif