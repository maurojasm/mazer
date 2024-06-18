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
        tile_sprites[TILE_GREEN].w = tile_texture.get_width() / 2;
        tile_sprites[TILE_GREEN].h = tile_texture.get_height();

        tile_sprites[TILE_BLACK].x = tile_texture.get_width() / 2;
        tile_sprites[TILE_BLACK].y = 0;
        tile_sprites[TILE_BLACK].w = tile_texture.get_width() / 2;
        tile_sprites[TILE_BLACK].h = tile_texture.get_height();
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
    // image ratios and dimesions
    double mi_ratio = 2.83, new_g_ratio = 5.97, op_ratio = 3.4, ex_ratio = 2.16;
    int mi_width = 600, mi_height = mi_width / mi_ratio,
        ng_w = SCREEN_WIDTH / 3.5, ng_h = ng_w / new_g_ratio,
        op_w = SCREEN_WIDTH / 5, op_h = op_w / op_ratio,
        ex_w = SCREEN_WIDTH / 8, ex_h = ex_w / ex_ratio;
    // create main menu that covers all the screen
    main_menu = new Menu("assets/media/png/menu/logo.png", SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // resize logo to specific dimention
    main_menu->set_main_image_dim(mi_width, mi_height);
    // set menu height offset
    main_menu->set_offset(50);
    // add options
    main_menu->add_option(ng_w, ng_h, "assets/media/png/menu/new_game.png");
    main_menu->add_option(op_w, op_h, "assets/media/png/menu/options.png");
    main_menu->add_option(ex_w, ex_h, "assets/media/png/menu/exit.png");

    double ea_ratio = 2.23, md_ratio = 4.9, hd_ratio = 2.99, mm_ratio = 6.27;
    int mm_w = SCREEN_WIDTH / 3.5, mm_h = mm_w / mm_ratio,
        ea_w = SCREEN_WIDTH / 8, ea_h = ea_w / ea_ratio,
        md_w = SCREEN_WIDTH / 5, md_h = md_w / md_ratio,
        hd_w = SCREEN_WIDTH / 8, hd_h = hd_w / hd_ratio;
    // create diff menu with no logo that covers all the screen
    difficulty_menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // set menu height offset
    difficulty_menu->set_offset(50);
    // add options
    difficulty_menu->add_option(ea_w, ea_h, "assets/media/png/menu/easy.png"); // easy
    difficulty_menu->add_option(md_w, md_h, "assets/media/png/menu/medium.png"); // medium
    difficulty_menu->add_option(hd_w, hd_h, "assets/media/png/menu/hard.png"); // hard
    difficulty_menu->add_option(mm_w, mm_h, "assets/media/png/menu/main_menu.png"); // main menu

    double con_ratio = 5.35;
    int con_w = SCREEN_WIDTH / 5, con_h = con_w / con_ratio;
    // create pause menu with no logo that covers all the screen
    pause_menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // set menu height offset
    pause_menu->set_offset(50);
    // add options
    pause_menu->add_option(con_w, con_h, "assets/media/png/menu/continue.png"); // continue
    pause_menu->add_option(mm_w, mm_h, "assets/media/png/menu/main_menu.png"); // main menu
    pause_menu->add_option(ex_w, ex_h, "assets/media/png/menu/exit.png"); // exit
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
        curr_diff = 0;
        set_level(curr_diff);
        play = true;
        active_difficulty_menu = false;
        break;
    case 1: // medium difficulty
        printf("Medium Difficulty!\n");
        curr_diff = 1;
        set_level(curr_diff);
        play = true;
        active_difficulty_menu = false;
        break;
    case 2: // hard difficulty
        printf("Difficult Difficulty!\n");
        curr_diff = 2;
        set_level(curr_diff);
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

    Player player1("assets/media/png/player/foo.png", renderer, 30, 60, 0, 160);
    player1.set_vel(3);
    player1.set_frames(4);
    player1.set_bullet_texture(&dot_texture);

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
                // player_handle_e();
                player1.handle_event(e);
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
            player1.move(LEVEL_WIDTH, LEVEL_HEIGHT, TOTAL_TILES, game_tiles);
            // dot.move(LEVEL_WIDTH, LEVEL_HEIGHT, TOTAL_TILES, game_tiles);
            // check if player has won
            if (player1.check_win(LEVEL_WIDTH, LEVEL_HEIGHT)) {
                printf("Player has won!\n");
                set_level(curr_diff);
                player1.reset_location();
            }
            // set camera over player
            player1.set_camera(camera, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);
            // dot.set_camera(camera, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);

            render_tiles();

            // render the dot
            player1.render(renderer, camera);
            // dot.render(dot_texture, camera, renderer);
        }
        //Update screen
        SDL_RenderPresent(renderer);
    }
}