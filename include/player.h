#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <vector>

#include "texture.h"
#include "tile.h"

/* Player class, allows to move and shoot inside of the level. */
class Player {
public:
    /*
    Player constructor - set initial position and player dimesions.
    */
    Player();
    /*
    Render dot texture to the screen.

    @param dot_texture  dot's texture to be render
    @param camera use   to determine dot's position of render
    @param renderer     renderer use to render the texture
    */
    void render(Texture& dot_texture, SDL_Rect& camera, SDL_Renderer* renderer);
private:
    // player location
    int x, y;

    // player velocity
    int vel;
};

#endif