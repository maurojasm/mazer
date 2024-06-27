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
#include "player.h"
#include "bullet.h"

/*
Game App
*/
class App {
public:
    /*
    Application contructor - handles initianization of SDL subprocesses.
    */
    App();

    /*
    Application destructor - handles deleting any memory and safely stop SDL subprocesses.
    */
    ~App();

    /*
    Start the application main (game) loop and handles any interactivity.
    */
    void start();
private:
    /*
    Game's difficulty levels.
    */
    enum Difficulty {
        EASY, MEDIUM, HARD
    };

    /*
    Loads initial assets such as game character and tiles png to create their textures.

    @return true if media was loaded successfully
    */
    bool load_media();

    /*
    Starts SDL subprocesses and creates window and renderer. Preset to this game specifications.

    @return true if initialization was successfull
    */
    bool init();

    /*
    Frees all media textures and deletes any dynamically allocated objects. Deletes window and renderer.
    And ends SDL subprocesses.
    */
    void close();

    /*
    Creates objects for each tile in the level map and sets the tiles sprites.

    @return true if success
    */
    bool set_tiles();

    /*
    Deletes all tiles objects in the level and resets vector to size 0.
    */
    void erase_tiles();

    /*
    Renders all tiles inside of the camera view.
    */
    void render_tiles();

    /*
    Creates the menu objects.
    */
    void set_menus();

    /*
    Creates main menu and adds pertinent options.
    */
    void set_main_menu();

    /*
    Creates difficulty menu and adds pertinent options.
    */
    void set_diff_menu();

    /*
    Creates pause menu and adds pertinent options.
    */
    void set_pause_menu();

    /*
    Sets player's default stats and texture as well as bullet texture.
    */
    void set_player();

    /*
    Sets the level difficulty and sets parameters for that given difficulty.

    @param difficutly enum struct that can be either: EASY, MEDIUM, HARD
    */
    void set_level(Difficulty difficulty);

    /*
    Makes the main menu handle the events and act accordingly.
    */
    void main_menu_handle_e();

    /*
    Makes the difficulty menu handle the events and act accordingly.
    */
    void diff_menu_handle_e();

    /*
    Makes the pause menu handle the events and act accordingly.
    */
    void pause_menu_handle_e();

    /*
    Makes the player handle the events and act accordingly.
    */
    void player_handle_e();

    // screen dimension constants
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    // default dimensions of the level
    int LEVEL_WIDTH = 1600;
    int LEVEL_HEIGHT = 1600;

    // default tile settings
    int TOTAL_TILES = 400;
    static const int TOTAL_TILE_SPRITES = 2;

    // tile sprites types
    const int TILE_GREEN = 0;
    const int TILE_BLACK = 1;

    // default maze dimensions
    int MAZE_DIM = 5;

    // default difficulty
    Difficulty curr_diff = EASY;

    // game states
    enum State {
        QUIT, MAIN_MENU, DIFF_MENU, PAUSE_MENU, PLAY
    };

    // default current game state
    State curr_state = MAIN_MENU;

    //The window to be render to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Scene textures
    Texture dot_texture;
    Texture tile_texture;

    //Event handler
    SDL_Event e;

    // Player object
    Player mc;

    // level camera
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // menus
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