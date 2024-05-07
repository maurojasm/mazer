#include <vector>
// #include <stdio.h>

#include "texture.h"
#include "menuItem.h"

using std::vector;
using std::string;

/*
Holds a list of MenuItems to interact with and an optional main image (logo).
*/
class Menu {
public:
    /*
    Class constructor. Menu contains main image (logo), usually for main menu.

    @param main_image_path  main image (logo) path to load
    @param width            width of menu
    @param height           height of menu
    @param renderer         pointer to desired renderer
    */
    Menu(string main_image_path, int m_width, int m_height, SDL_Renderer* renderer);

    /*
    (overload) Class constructor. Menu does not have a main image (logo).

    @param width            width of menu
    @param height           height of menu
    @param renderer         pointer to desired renderer
    */
    Menu(int m_width, int m_height, SDL_Renderer* renderer);

    /*
    Class destructor. Deletes all menu items and frees menu textures.
    */
    ~Menu();

    /*
    Adds MenuItem to Menu.

    @param width        witdh of menu item. If not specified, set to width of image
    @param height       height of menu item. If not specified, set to height of image
    @param texture_path path of image to create texture. If not specified, set to default image
    */
    void add_option(int op_width = 0, int op_height = 0, string texture_path = "assets/media/png/menu/option_button.png");

    /*
    Renders all items in the menu, including main image (logo) if it exits.
    */
    void render();

    /*
    Passes event to menu items for interactivity and returns which item was pressed

    @param e SDL event to be handle
    @return item which was pressed. -1 if none was
    */
    int handle_event(SDL_Event* e);

    /*
    Sets main image (logo) dimension.

    @param width    new width to be set
    @param height   new height to be set
    */
    void set_main_image_dim(int new_width, int new_height);

    /*
    Sets height offset between menu items.

    @param offset height offset in pixel count
    */
    void set_offset(int offset) { this->h_offset = offset; }

private:
    /*
    Render main image of the menu (usually logo)
    */
    void render_main_image();

    /*
    Render all menu items (options)
    */
    void render_items();

    /*
    Rearranges the positions of the logo and menu items to center all of them.
    */
    void rearrange_items();

    // menu dimensions
    int m_width, m_height;
    // menu location
    int m_x = 0, m_y = 0;

    // flag for main image (logo)
    bool is_main_image = false;
    // main image dimensions
    int mi_width, mi_height;
    // main image location
    int mi_x = 0, mi_y = 0;

    // default background image path
    string background_path = "assets/media/png/menu/background.png";

    // menu textures
    Texture main_image;
    Texture background;

    // menu renderer
    SDL_Renderer* m_renderer;

    // list of menu items
    vector<MenuItem*> menu_items;

    // height offset between menu items
    int h_offset = 10;
};