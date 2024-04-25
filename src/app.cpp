#include "../include/app.h"

App::App() {
    if (!init()) {
        printf("Failed to initialize!\n");
        exit(1);
    }
}

App::~App() {
    close();
}

bool App::init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        window = SDL_CreateWindow("Mazer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool App::load_media() {
    // sucess variable
    bool success = true;

    // load dot texture
    int rgb[] = { 0x00, 0xFF, 0xFF }; // color values to make transparent
    if (!dot_texture.load_from_file("assets/media/bmp/dot.bmp", renderer, true, rgb)) {
        printf("Falied to load dot texture!\n");
        success = false;
        return success;
    }
    // load tile texture
    if (!tile_texture.load_from_file("assets/media/png/tiles/tiles.png", renderer)) {
        printf("Falied to load tile texture!\n");
        success = false;
        return success;
    }

    return success;
}

bool App::set_tiles() {
    // delete current tiles
    erase_tiles();
    // success flag
    bool tiles_loaded = true;

    // coordinates offset
    int x = 0, y = 0;

    // get map from maze
    string map = my_maze->get_map();

    for (int i = 0; i < TOTAL_TILES; i++) {
        // type of tile
        int tile_type = -1;
        tile_type = map[i] - '0';

        // check if tile type is correct
        if (tile_type >= 0 && tile_type < TOTAL_TILE_SPRITES) {
            game_tiles.push_back(new Tile(x, y, tile_type));
        } //If we don't recognize the tile type
        else {
            //Stop loading map
            printf("Error loading map: Invalid tile type at %d!\n", i);
            tiles_loaded = false;
            return tiles_loaded;
        }

        //Move to next tile spot
        x += game_tiles[i]->get_width();

        //If we've gone too far
        if (x >= LEVEL_WIDTH) {
            //Move back
            x = 0;

            //Move to the next row
            y += game_tiles[i]->get_height();
        }

    }

    // set sprites from tiles.png
    if (tiles_loaded) {
        tile_sprites[TILE_GREEN].x = 0;
        tile_sprites[TILE_GREEN].y = 0;
        tile_sprites[TILE_GREEN].w = game_tiles[0]->get_width();
        tile_sprites[TILE_GREEN].h = game_tiles[0]->get_height();

        tile_sprites[TILE_BLACK].x = 80;
        tile_sprites[TILE_BLACK].y = 0;
        tile_sprites[TILE_BLACK].w = game_tiles[0]->get_width();
        tile_sprites[TILE_BLACK].h = game_tiles[0]->get_height();
    }

    // return if success on loading
    return tiles_loaded;
}

void App::erase_tiles() {
    if (game_tiles.size() == 0) { return; }

    for (unsigned i = 0; i < game_tiles.size(); i++) {
        if (game_tiles[i] != NULL) {
            delete game_tiles[i];
            game_tiles[i] = NULL;
        }
    }
    game_tiles.clear();
}

void App::render_tiles() {
    // render each tile from level in camera's field of view
    for (int i = 0; i < TOTAL_TILES; i++) {
        game_tiles[i]->render(camera, tile_texture, tile_sprites, renderer);
    }
}

void App::close() {
    // free all tiles
    printf("-- Erasing all Tiles...\n");
    erase_tiles();
    // Delete maze and menu objects
    printf("-- Erasing Maze...\n");
    if (my_maze != NULL) { delete my_maze; my_maze = NULL; }
    printf("-- Erasing Main Menu...\n");
    if (main_menu != NULL) { delete main_menu; main_menu = NULL; }
    printf("-- Erasing Diff Menu...\n");
    if (difficulty_menu != NULL) { delete difficulty_menu; difficulty_menu = NULL; }
    printf("-- Erasing Pause Menu...\n");
    if (pause_menu != NULL) { delete pause_menu; pause_menu = NULL; }

    //Free loaded images
    printf("-- Erasing Textures...\n");
    dot_texture.free();
    tile_texture.free();

    //Destroy window and renderer
    printf("-- Erasing Window and Renderer...\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    printf("-- Quitting SDL subsystems...\n");
    IMG_Quit();
    SDL_Quit();

    printf("*** All processes exited successfully! ***\n");
}

void App::set_menu() {
    // create main menu that covers all the screen
    main_menu = new Menu("assets/media/png/default.png", SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // resize logo to specific dimention
    main_menu->set_main_image_dim(300, 200);
    // add options
    main_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    main_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    main_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);

    // create diff menu with no logo that covers all the screen
    difficulty_menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // // add options 
    difficulty_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    difficulty_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    difficulty_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    difficulty_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);

    // // create pause menu with no logo that covers all the screen
    pause_menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // // add options
    pause_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    pause_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
    pause_menu->add_option(SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 5);
}

void App::set_level(int difficulty) {
    if (difficulty == 0) { // easy 5x5 maze
        MAZE_DIM = 5;

        LEVEL_WIDTH = 1600;
        LEVEL_HEIGHT = 1600;

        TOTAL_TILES = 400;
    }
    else if (difficulty == 1) { // medium 8x8 maze
        MAZE_DIM = 8;

        LEVEL_WIDTH = 2560;
        LEVEL_HEIGHT = 2560;

        TOTAL_TILES = 1024;
    }
    else if (difficulty == 2) { // hard 10x10 maze
        MAZE_DIM = 10;

        LEVEL_WIDTH = 3200;
        LEVEL_HEIGHT = 3200;

        TOTAL_TILES = 1600;
    }
    else {
        printf("Incompabile Difficulty!\n");
        return;
    }
    if (my_maze == NULL) { // create maze object
        my_maze = new Maze(MAZE_DIM);

        if (!set_tiles()) { // set tiles to specific level
            printf("Falied to set tiles!\n");
            return;
        }
    }
    else {
        delete my_maze;
        my_maze = new Maze(MAZE_DIM);

        if (!set_tiles()) { // set tiles to specific level
            printf("Falied to set tiles!\n");
            return;
        }

        // reset dot location
        dot.reset_location();
    }
}

void App::main_menu_handle_e() {
    // get which button was pressed
    button_pressed = main_menu->handle_event(&e);

    switch (button_pressed) {
    case 0: // start game, show difficulty menu
        active_main_menu = false;
        active_difficulty_menu = true;
        break;
    case 1: // @todo shows options menu
        printf("Select options\n");
        break;
    case 2: // exit the game
        quit = true;
        break;
    }
}

void App::diff_menu_handle_e() {
    // get which button was pressed
    button_pressed = difficulty_menu->handle_event(&e);

    switch (button_pressed) {
    case 0: // easy difficulty
        printf("Easy Difficulty!\n");
        set_level(0);
        play = true;
        active_difficulty_menu = false;
        break;
    case 1: // medium difficulty
        printf("Medium Difficulty!\n");
        set_level(1);
        play = true;
        active_difficulty_menu = false;
        break;
    case 2: // hard difficulty
        printf("Difficult Difficulty!\n");
        set_level(2);
        play = true;
        active_difficulty_menu = false;
        break;
    case 3: // goes back to main menu
        active_main_menu = true;
        active_difficulty_menu = false;
        break;
    }
}

void App::pause_menu_handle_e() {
    // get which button was pressed
    button_pressed = pause_menu->handle_event(&e);

    switch (button_pressed) {
    case 0: // resume game
        play = true;
        active_pause_menu = false;
        break;
    case 1:
        play = false;
        active_main_menu = true;
        active_difficulty_menu = false;
        active_pause_menu = false;
        break;
    case 2: // quit game
        quit = true;
        break;
    }
}

void App::player_handle_e() {
    // player object handles event 
    dot.handle_event(e);
}

void App::start() {
    // load media
    if (!load_media()) {
        printf("Failed to load media!\n");
        return;
    }
    set_menu();

    //app running
    while (!quit) {
        // handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // user requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (active_main_menu) {
                main_menu_handle_e();
            }
            else if (active_difficulty_menu) {
                diff_menu_handle_e();
            }
            else if (play) {
                player_handle_e();
                // check for pause
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        play = false;
                        active_pause_menu = true;
                    }
                }
            }
            else if (active_pause_menu) {
                pause_menu_handle_e();
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // render active game state
        if (active_main_menu) {
            main_menu->render();
        }
        else if (active_difficulty_menu) {
            difficulty_menu->render();
        }
        else if (active_pause_menu) {
            pause_menu->render();
        }
        else if (play) {
            // move dot
            dot.move(LEVEL_WIDTH, LEVEL_HEIGHT, TOTAL_TILES, game_tiles);
            // check if player has won
            if (dot.check_win(LEVEL_WIDTH, LEVEL_HEIGHT)) {
                printf("Player has won!\n");
            }
            // set camera over player
            dot.set_camera(camera, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);

            render_tiles();

            // render the dot
            dot.render(dot_texture, camera, renderer);
        }
        //Update screen
        SDL_RenderPresent(renderer);
    }
}