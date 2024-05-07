#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

class Texture {
public:
    /*
    Class constructor - initialize texture and demensions to NULL and 0's.
    */
    Texture();

    /*
    Class destructor - calls free function.
    */
    ~Texture();

    /*
    Creates texture from specified png file.

    @param path         path to png file
    @param renderer     renderer used to render texture
    @param color_key    flag to color key the texture
    @param rgb          if color_key flag is true, array holds RGB values to key
    @return true if creating texture was successfull
    */
    bool load_from_file(std::string path, SDL_Renderer* renderer, bool color_key = false, int rgb[3] = NULL);

    /*
    Deletes SDL texture object and sets image dimensions to 0.
    */
    void free();

    /*
    Sets texture's color modulation.

    @param red      red value
    @param green    green value
    @param blue     blue value
    */
    void set_color(Uint8 red, Uint8 green, Uint8 blue);

    /*
    Sets texture's blending.

    @param blending the SDL_BlendMode to use for texture blending
    */
    void set_blend_mode(SDL_BlendMode blending);

    /*
    Sets texture's alpha value.

    @param alpha    alpha value
    */
    void set_alpha(Uint8 alpha);

    /*
    Renders texture to screen.

    @param x            x-coordinate position
    @param y            y-coordinate position
    @param renderer     the rendering context
    @param clip         the source SDL_Rect structure or NULL for the entire texture
    @param renderQuad   the destination SDL_Rect structure or NULL for the entire rendering target
    @param angle        an angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction
    @param center       a pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2)
    @param flip         a SDL_RendererFlip value stating which flipping actions should be performed on the texture
    */
    void render(int x, int y, SDL_Renderer* renderer,
        SDL_Rect* clip = NULL, SDL_Rect* renderQuad = NULL, double angle = 0.0,
        SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    /* ---- Getter functions ---- */

    int get_width();
    int get_height();

    /* -------------------------- */

private:
    // actual texture
    SDL_Texture* texture;

    // image dimensions
    int t_width, t_height;
};

#endif