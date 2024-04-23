#include <vector>
// #include <stdio.h>

#include "texture.h"
#include "menuItem.h"

using std::vector;
using std::string;

class Menu {
public:
    /*
    Class constructor. Menu contains main image (logo), usually for main menu.
    @param main_image_path  main image (logo) path to load
    @param width            width of menu
    @param height           height of menu
    @param renderer         pointer to desired renderer
    */
    Menu(string main_image_path, int width, int height, SDL_Renderer* renderer);

    /*
    (overload) Class constructor. Menu does not have a main image (logo).
    @param width            width of menu
    @param height           height of menu
    @param renderer         pointer to desired renderer
    */
    Menu(int width, int height, SDL_Renderer* renderer);

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
    void add_option(int width = 0, int height = 0, string texture_path = "assets/media/png/menu/option_button.png");

    /*
    Renders all items in the menu, including main image (logo) if it exits.
    */
    void render();

    /*
    Passes event to menu items for interactivity and returns which item was pressed
    @param e SDL event to be handle
    @return item which was pressed. -1 if non was
    */
    int handle_event(SDL_Event* e);

    /*
    Sets main image (logo) dimension
    @param width    new width to be set
    @param height   new height to be set
    */
    void set_main_image_dim(int width, int height);

private:
    /*
    Render main image of the menu (usually logo)
    */
    void render_main_image();

    /*
    Render all menu items (options)
    */
    void render_items();

    // menu dimensions
    int width, height;
    // menu location
    int x = 0, y = 0;

    // flag for main image (logo)
    bool is_main_image = false;
    // main image dimensions
    int mi_width, mi_height;
    // main image location
    int mi_x, mi_y;

    // location of last item in menu
    int last_x, last_y;

    // default background image path
    string background_path = "assets/media/png/menu/grey_background.png";

    // menu textures
    Texture main_image;
    Texture background;

    // menu renderer
    SDL_Renderer* m_renderer;

    // list of menu items
    vector<MenuItem*> menu_items;
};