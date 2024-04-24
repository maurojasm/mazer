#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
// #include <stdio.h>
#include <string>
#include <vector>

#include "texture.h"
#include "tile.h"

/*
Holds Dot that is able to move around the level.
*/
class Dot {
public:
    /*
    Dot constructor - sets initial position and dot dimensions.
    */
    Dot();

    /*
    Render dot texture to the screen.

    @param dot_texture  dot's texture to be render
    @param camera use   to determine dot's position of render
    @param renderer     renderer use to render the texture
    */
    void render(Texture& dot_texture, SDL_Rect& camera, SDL_Renderer* renderer);

    /*
    Handles key presses

    @param e event to handle
    */
    void handle_event(SDL_Event& e);

    /*
    Move the dot within the level bounds and check for collision

    @param LEVEL_HEIGHT height of the level
    @param LEVEL_WIDTH  width of the level
    @param TOTAL_TILES  total number of tiles in the level
    @param game_tiles   list of the level's Tile* objects
    */
    void move(int LEVEL_HEIGHT, int LEVEL_WIDTH, int TOTAL_TILES, std::vector<Tile*> game_tiles);

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

private:
    // dot dimensions
    static const int d_height = 20;
    static const int d_width = 20;

    // max dot velocity
    static const int max_vel = 8;

    // dot's collision box
    SDL_Rect hit_box;

    // velocity of the dot
    int x_vel, y_vel;
};

#endif