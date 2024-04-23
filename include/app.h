#ifndef MY_APP
#define MY_APP

//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "dot.h"
#include "tile.h"
#include "texture.h"
#include "maze.h"
#include "menu.h"

class App {
public:
    // constructor
    App();

    // destructor
    ~App();

    // starts application 
    void start();
private:
    //Loads media
    bool load_media();

    //Starts up SDL and creates window
    bool init();

    //Frees media and shuts down SDL
    void close();

    // set tiles from maze map
    bool set_tiles();
    void render_tiles();

    void set_menu();

    void set_level(int difficulty);

    void main_menu_handle_e();

    void diff_menu_handle_e();

    void pause_menu_handle_e();

    void player_handle_e();

    //Screen dimension constants
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    //default dimensions of the level
    int LEVEL_WIDTH = 1600;
    int LEVEL_HEIGHT = 1600;

    // tile settings
    int TOTAL_TILES = 400;
    static const int TOTAL_TILE_SPRITES = 2;

    // different tile sprites
    const int TILE_GREEN = 0;
    const int TILE_BLACK = 1;

    // default maze dimensions
    int MAZE_DIM = 5;

    // flags
    bool quit = false,
        active_main_menu = true,
        active_difficulty_menu = false,
        active_pause_menu = false,
        play = false;

    // button option
    int button_pressed;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Scene textures
    Texture dot_texture;
    Texture tile_texture;

    //Event handler
    SDL_Event e;

    // dot moving around the screen
    Dot dot;

    // level camera
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    Menu* main_menu = NULL;
    Menu* difficulty_menu = NULL;
    Menu* pause_menu = NULL;

    // maze to traverse
    Maze* my_maze = NULL;

    // tiles required for level
    std::vector<Tile*> game_tiles;

    // sprites from tile texture
    SDL_Rect tile_sprites[TOTAL_TILE_SPRITES];
};

#endif