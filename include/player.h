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
    /*
    Class constructor, allows for simple creation with default parameters.

    @param w width of player's hitbox
    @param h height of player's hitbox
    @param x x-coordinate location of player's hitbox
    @param y y-coordinate location of player's hitbot
    */
    Player(int w = 20, int h = 20, int x = 0, int y = 0);

    /*
    Class constructor, (overload) image path is passed as well as renderer.

    @param im_path  image path to create texture from
    @param renderer renderer to create the texture from
    @param key      boolean flag to determine color keying
    @param rgb      array of int values representing RGB values in that order.
    @param w        width of player's hitbox
    @param h        height of player's hitbox
    @param x        x-coordinate location of player's hitbox
    @param y        y-coordinate location of player's hitbot
    */
    Player(string im_path, SDL_Renderer* renderer, bool key = false, int rgb[3] = NULL, int w = 20, int h = 20, int x = 0, int y = 0);

    /*
    Sets player movement's velocity.

    @param vel integer representing number of pixels per cycle of movement
    */
    void set_vel(int vel);

    /*
    Sets amount of frames in player's movement animantion. For now, it expects the player's texture
    to be comprise of all frames in animation, as it will clip the texture by the amount of frames given.

    @param frames unsigned integer representing number of frames of animation
    */
    void set_frames(unsigned frames);

    /*
    Sets the size of the player's hitbox. This will also be reflected in the size of rendered image.

    @param w width of player's hitbox
    @param h height of player's hitbox
    */
    void set_size(int w, int h);

    /*
    Sets position of player's hitbox.

    @param x x-coordinate location of player's hitbox
    @param y y-coordinate location of player's hitbot
    */
    void set_pos(int x, int y);

    /*
    Wrapper function to set all player's dimensions.

    @param w         width of player's hitbox
    @param h         height of player's hitbox
    @param x         x-coordinate location of player's hitbox
    @param y         y-coordinate location of player's hitbot
    @param vel       integer representing number of pixels per cycle of movement
    @param frames    unsigned integer representing number of frames of animation
    @param direction direction the player will be facing
    */
    void set_dims(int w, int h, int x, int y, int vel, unsigned frames, Direction direction);

    /*
    Sets the current bullet's texture.

    @param texture Texture object that will be used when rendering the bullet
    */
    void set_bullet_texture(Texture* texture);

    /*
    Sets the player's texture. Allows for color keying.

    @param im_path  image path to create texture from
    @param renderer renderer to create the texture from
    @param key      boolean flag to determine color keying
    @param rgb      array of int values representing RGB values in that order.
    */
    void set_player_texture(string im_path, SDL_Renderer* renderer, bool key = false, int rgb[3] = NULL);

    /*
    Handle events from user. For now is movement and shooting.

    @param e SDL_Event objects from event queue
    */
    void handle_event(SDL_Event& e);

    /*
    Moves player based on previus calculated velocity. Checks for collisions.

    @param LEVEL_HEIGHT height of current level in pixels
    @param LEVEL_WIDTH  width of current level in pixels
    @param game_tiles   vector of tile objects to check for collisions
    */
    void move(int LEVEL_HEIGHT, int LEVEL_WIDTH, std::vector<Tile*> game_tiles);

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

    @param game_tiles   vector of tile objects to check for collisions
    @return             true if dot touches a wall
    */
    bool touches_wall(std::vector<Tile*> game_tiles);

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
    void reset_location(int x, int y);

private:
    /*
    Moves all bullets every cycle.

    @param level_w      width of the level to check for boundary
    @param level_h      height of the level to check for boundary
    @param game_tiles   vector of tile objects to check for collisions
    */
    void move_bullets(int level_w, int level_h, vector<Tile*> game_tiles);

    // player's hitbox dimensions
    int p_width, p_height;

    // velocity variables
    int p_vel, vel_x, vel_y;

    // frame variables
    int curr_frame, num_frames;

    // player's hitbox
    SDL_Rect hit_box;

    // Direction where the player is facing
    Direction dir;

    // vector of clips per frame based on player's texture
    vector<SDL_Rect> frame_clips;

    // player's texture 
    Texture player_texture;

    // bullet texture. will add more so we can have different types
    Texture* bullet_texture;

    // vector of bullet objects currently on level
    vector<Bullet> bullets;
};

#endif