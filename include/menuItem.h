#include "texture.h"

using std::string;

/*
Interactive menu button
*/
class MenuItem {
public:
    /*
    Class Constructor - creates a menuItem with a desired texture and size.

    @param path     png image path
    @param renderer renderer used to render the texture
    @param width    desired width of the button, if not specified, width is set to texture's width
    @param height   desired height of the button, if not specified, height is set to texture's height
    */
    MenuItem(string path, SDL_Renderer* renderer, int width = 0, int height = 0);

    /*
    Class destructor - frees texture and set renderer to NULL.
    */
    ~MenuItem();

    /*
    Sets button position in the screen.

    @param x    x-coordinate
    @param y    y-coordinate
    */
    void set_position(int x, int y);

    /*
    Sets button dimensions.

    @param width    width in pixels
    @param height   height in pixels
    */
    void set_dimesions(int width, int height);

    /*
    Handles user events for interacitivty.

    @param e    SDL event
    @return true if button was pressed
    */
    bool handle_event(SDL_Event* e);

    /*
    Renders button to screen.

    @param clip         clip of texture to render, if not specified, render whole texture
    @param renderQuad   quad to render, used to resize texture to desired size. If not specified, render original texture size.
    */
    void render(SDL_Rect* clip = NULL, SDL_Rect* renderQuad = NULL);

    /* ---- Getter functions ---- */

    int get_texture_width() { return item_width; }
    int get_texture_height() { return item_height; }
    int get_x() { return x; }
    int get_y() { return y; }

    /* --------------------------- */

private:
    // button dimensions
    int item_width, item_height;
    // button position
    int x = 0, y = 0;

    // button renderer
    SDL_Renderer* item_renderer;

    // button texture
    Texture item_texture;
};