#include "../include/texture.h"

Texture::Texture() {
    // initialize
    texture = NULL;
    t_width = 0;
    t_height = 0;
}

Texture::~Texture() {
    // deallocate mem
    free();
}

bool Texture::load_from_file(std::string path, SDL_Renderer* renderer, bool color_key, int rgb[3]) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    else {
        if (color_key) {
            //Color key image
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, rgb[0], rgb[1], rgb[2]));
        }
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }
        else {
            //Get image dimensions
            t_width = loadedSurface->w;
            t_height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    texture = newTexture;
    return texture != NULL;
}

void Texture::free() {
    // free texture if it exists
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        t_width = 0;
        t_height = 0;
    }
}

void Texture::set_color(Uint8 red, Uint8 green, Uint8 blue) {
    //Modulate texture rgb
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::set_blend_mode(SDL_BlendMode blending) {
    //Set blending function
    SDL_SetTextureBlendMode(texture, blending);
}

void Texture::set_alpha(Uint8 alpha) {
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::render(int x, int y, SDL_Renderer* renderer,
    SDL_Rect* clip, SDL_Rect* renderQuad, double angle,
    SDL_Point* center, SDL_RendererFlip flip) {
    bool dyn_alloc = false;
    if (renderQuad == NULL) {
        // set render space and render to screen
        renderQuad = new SDL_Rect{ x, y, t_width, t_height };
        dyn_alloc = true;
    }

    // set clip rendering dimensions
    if (clip != NULL) {
        renderQuad->w = clip->w;
        renderQuad->h = clip->h;
    }

    // render to screen
    SDL_RenderCopyEx(renderer, texture, clip, renderQuad, angle, center, flip);
    if (dyn_alloc) { delete renderQuad; }
}

int Texture::get_width() {
    return t_width;
}

int Texture::get_height() {
    return t_height;
}