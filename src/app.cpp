//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "../include/app.h"

App::App() {
    if(!init()) {
        printf( "Failed to initialize!\n" );
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
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        window = SDL_CreateWindow( "Mazer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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
    if(!dot_texture.load_from_file("assets/media/bmp/dot.bmp", renderer)) {
        printf("Falied to load dot texture!\n");
        success = false;
        return success;
    }
    if(!tile_texture.load_from_file("assets/media/png/tiles/tiles.png", renderer)) {
        printf("Falied to load tile texture!\n");
        success = false;
        return success;
    }
    if(!set_tiles()) {
        printf("Falied to set tiles!\n");
        success = false;
        return success;
    }

    return success;
}

bool App::set_tiles() {
    // success flag
    bool tiles_loaded = true;
    
    // coordinates offset
    int x = 0, y = 0;

    // get map from maze
    string map = my_maze.get_map();

    for(int i = 0; i < TOTAL_TILES; i++) {
        // type of tile
        int tile_type = -1;
        tile_type = map[i] - '0';

        if(tile_type >= 0 && tile_type < TOTAL_TILE_SPRITES) {
            game_tiles[i] = new Tile(x, y, tile_type);
        } //If we don't recognize the tile type
        else {
            //Stop loading map
            printf( "Error loading map: Invalid tile type at %d!\n", i );
            tiles_loaded = false;
            return tiles_loaded;
        }

        //Move to next tile spot
        x += game_tiles[i] -> get_width();

        //If we've gone too far
        if( x >= LEVEL_WIDTH ) {
            //Move back
            x = 0;

            //Move to the next row
            y += game_tiles[i] -> get_height();
        }
        
    }
    
    // set sprites from tiles.png
    if(tiles_loaded) {
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

void App::close() {
    // free all tiles
    for(int i = 0; i < TOTAL_TILES; i++) {
        if(game_tiles[i] != NULL) {
            delete game_tiles[i];
            game_tiles[i] = NULL;
        }
    }
    //Free loaded images
    dot_texture.free();
    tile_texture.free();

    //Destroy window	
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    printf("All processes exited successfully.\n");
}

void App::start() {
    // load media
    if(!load_media()) {
        printf("Failed to load media!\n");
        return;
    }
    bool quit = false;

    //Event handler
    SDL_Event e;

    // dot moving around the screen
    Dot dot;

    // level camera
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    //app running
    while(!quit) {
        // handle events on queue
        while(SDL_PollEvent(&e) != 0) {
            // user requests quit
            if(e.type == SDL_QUIT) {
                quit = true;
            }

            // handle input
            dot.handle_event(e);
        }
        // move dot
        dot.move(LEVEL_WIDTH, LEVEL_HEIGHT);
        dot.set_camera(camera, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(renderer);

        // render each tile from level
        for(int i = 0; i < TOTAL_TILES; i++) {
            game_tiles[i] -> render(camera, tile_texture, tile_sprites, renderer);
        }

        // render the dot
        dot.render(dot_texture, camera, renderer);

        //Update screen
        SDL_RenderPresent(renderer);
    }
}