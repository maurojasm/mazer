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

	return success;
}

void App::close() {
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

		dot.render(dot_texture, camera, renderer);

        //Update screen
        SDL_RenderPresent(renderer);
    }
}