#include "../include/app.h"

App::App() {
    // initialize SDL subsystems
    if (!init()) {
        printf("Failed to initialize!\n");
        exit(1);
    }
}

App::~App() {
    // call close function 
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
        // substract ascii char offset
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

        //If we've gone too far start new row
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
            delete game_tiles[i]; // calls ~Tile()
            game_tiles[i] = NULL;
        }
    }
    // remove all pointers from vector
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

void App::set_menus() {
    // set all menus
    set_main_menu();
    set_diff_menu();
    set_pause_menu();
}

void App::set_main_menu() {
    // image ratios
    double mi_ratio = 2.83, new_g_ratio = 5.97, op_ratio = 3.4, ex_ratio = 2.16;
    // image dimensions based on screen width and image ratios
    int mi_width = 600, mi_height = mi_width / mi_ratio,        // main image
        ng_w = SCREEN_WIDTH / 3.5, ng_h = ng_w / new_g_ratio,   // new game
        op_w = SCREEN_WIDTH / 5, op_h = op_w / op_ratio,        // options
        ex_w = SCREEN_WIDTH / 8, ex_h = ex_w / ex_ratio;        // exit
    // create main menu that covers all the screen
    main_menu = new Menu("assets/media/png/menu/logo.png", SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // resize logo to specific dimention
    main_menu->set_main_image_dim(mi_width, mi_height);
    // set menu height offset in pixels
    main_menu->set_offset(50);
    // add options
    main_menu->add_option(ng_w, ng_h, "assets/media/png/menu/new_game.png"); // new game
    main_menu->add_option(op_w, op_h, "assets/media/png/menu/options.png");  // options
    main_menu->add_option(ex_w, ex_h, "assets/media/png/menu/exit.png");     // exit game
}

void App::set_diff_menu() {
    // image ratios
    double ea_ratio = 2.23, md_ratio = 4.9, hd_ratio = 2.99, mm_ratio = 6.27;
    // image dimensions based on screen width and image ratios
    int mm_w = SCREEN_WIDTH / 3.5, mm_h = mm_w / mm_ratio,  // main menu
        ea_w = SCREEN_WIDTH / 8, ea_h = ea_w / ea_ratio,    // easy
        md_w = SCREEN_WIDTH / 5, md_h = md_w / md_ratio,    // medium
        hd_w = SCREEN_WIDTH / 8, hd_h = hd_w / hd_ratio;    // hard
    // create diff menu with no logo that covers all the screen
    difficulty_menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // set menu height offset
    difficulty_menu->set_offset(50);
    // add options
    difficulty_menu->add_option(ea_w, ea_h, "assets/media/png/menu/easy.png");      // easy
    difficulty_menu->add_option(md_w, md_h, "assets/media/png/menu/medium.png");    // medium
    difficulty_menu->add_option(hd_w, hd_h, "assets/media/png/menu/hard.png");      // hard
    difficulty_menu->add_option(mm_w, mm_h, "assets/media/png/menu/main_menu.png"); // main menu
}

void App::set_pause_menu() {
    // image ratios
    double con_ratio = 5.35, mm_ratio = 6.27, ex_ratio = 2.16;
    // image dimensions based on screen width and image ratios
    int mm_w = SCREEN_WIDTH / 3.5, mm_h = mm_w / mm_ratio,    // main menu
        ex_w = SCREEN_WIDTH / 8, ex_h = ex_w / ex_ratio,      // exit
        con_w = SCREEN_WIDTH / 5, con_h = con_w / con_ratio;  // continue
    // create pause menu with no logo that covers all the screen
    pause_menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
    // set menu height offset
    pause_menu->set_offset(50);
    // add options
    pause_menu->add_option(con_w, con_h, "assets/media/png/menu/continue.png"); // continue
    pause_menu->add_option(mm_w, mm_h, "assets/media/png/menu/main_menu.png");  // main menu
    pause_menu->add_option(ex_w, ex_h, "assets/media/png/menu/exit.png");       // exit
}

void App::set_level(Difficulty difficulty) {
    // set maze dimension based on difficulty
    switch (difficulty) {
    case EASY: // 5x5 maze
        MAZE_DIM = 5;
        break;
    case MEDIUM: // 8x8 maze
        MAZE_DIM = 8;
        break;
    case HARD: // 10x10 maze
        MAZE_DIM = 10;
        break;
    default:
        printf("Incompabile Difficulty!\n");
        return;
    }
    // set level dimensions based on maze dimension
    LEVEL_WIDTH = 4 * 80 * MAZE_DIM;  // 4 tiles of 80 px per cell
    LEVEL_HEIGHT = LEVEL_WIDTH;       // square maze
    TOTAL_TILES = (4 * MAZE_DIM) * (4 * MAZE_DIM); // square maze

    // create maze object if none
    if (my_maze == NULL) {
        my_maze = new Maze(MAZE_DIM);
        // set tiles to specific level
        if (!set_tiles()) {
            printf("Falied to set tiles!\n");
            return;
        }
    }
    else { // level is reset or new difficulty has been set
        delete my_maze;
        my_maze = new Maze(MAZE_DIM);

        if (!set_tiles()) { // set tiles to specific level
            printf("Falied to set tiles!\n");
            return;
        }

        // reset player location
        mc.reset_location(0, 160);
    }
}

void App::set_player() {
    // blue hue to remove
    int rgb[] = { 0, 0xFF, 0xFF };
    // set player texture and color key blue background
    mc.set_player_texture("assets/media/png/player/foo.png", renderer, true, rgb);
    // set player dimensions: width, height, x, y, vel, frames, and direction
    mc.set_dims(30, 60, 0, 160, 3, 4, RIGHT_DIR);
    mc.set_bullet_texture(&dot_texture);
}

void App::main_menu_handle_e() {
    // get which button was pressed
    int button_pressed = main_menu->handle_event(&e);

    switch (button_pressed) {
    case 0: // start game, show difficulty menu
        curr_state = DIFF_MENU;
        break;
    case 1: // @todo shows options menu
        printf("Select options\n");
        break;
    case 2: // exit the game
        curr_state = QUIT;
        break;
    }
}

void App::diff_menu_handle_e() {
    // get which button was pressed
    int button_pressed = difficulty_menu->handle_event(&e);

    switch (button_pressed) {
    case 0: // easy difficulty
        printf("Easy Difficulty!\n");
        curr_diff = EASY;
        set_level(curr_diff);
        curr_state = PLAY;
        break;
    case 1: // medium difficulty
        printf("Medium Difficulty!\n");
        curr_diff = MEDIUM;
        set_level(curr_diff);
        curr_state = PLAY;
        break;
    case 2: // hard difficulty
        printf("Hard Difficulty!\n");
        curr_diff = HARD;
        set_level(curr_diff);
        curr_state = PLAY;
        break;
    case 3: // goes back to main menu
        curr_state = MAIN_MENU;
        break;
    }
}

void App::pause_menu_handle_e() {
    // get which button was pressed
    int button_pressed = pause_menu->handle_event(&e);

    switch (button_pressed) {
    case 0: // resume game
        curr_state = PLAY;
        break;
    case 1: // main menu
        curr_state = MAIN_MENU;
        break;
    case 2: // quit game
        curr_state = QUIT;
        break;
    }
}

void App::player_handle_e() {
    // player object handles event 
    mc.handle_event(e);
}

void App::start() {
    // load media
    if (!load_media()) {
        printf("Failed to load media!\n");
        return;
    }
    // set menus and player objects
    set_menus();
    set_player();

    //app running
    while (curr_state != QUIT) {
        // handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // user requests quit
            if (e.type == SDL_QUIT) {
                curr_state = QUIT;
            }

            switch (curr_state) {
            case MAIN_MENU:
                main_menu_handle_e();
                break;
            case DIFF_MENU:
                diff_menu_handle_e();
                break;
            case PLAY:
                player_handle_e();
                // check for pause button (esc)
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        curr_state = PAUSE_MENU;
                    }
                }
                break;
            case PAUSE_MENU:
                pause_menu_handle_e();
                break;
            case QUIT:
                return;
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // render active game state
        switch (curr_state) {
        case MAIN_MENU:
            main_menu->render();
            break;
        case DIFF_MENU:
            difficulty_menu->render();
            break;
        case PLAY:
            // move player 
            mc.move(LEVEL_WIDTH, LEVEL_HEIGHT, game_tiles);
            // check if player is in winning zone
            if (mc.check_win(LEVEL_WIDTH, LEVEL_HEIGHT)) {
                printf("Player has won!\n");
                // reset level and player location
                set_level(curr_diff);
                mc.reset_location(0, 160);
            }
            // set camera to top of player
            mc.set_camera(camera, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);

            // render tiles in camera space
            render_tiles();

            // render player relative to camera
            mc.render(renderer, camera);
            break;
        case PAUSE_MENU:
            pause_menu->render();
            break;
        case QUIT:
            return;
        }
        //Update screen
        SDL_RenderPresent(renderer);
    }
}