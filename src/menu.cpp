#include "../include/menu.h"

Menu::Menu(string main_image_path, int width, int height, SDL_Renderer* renderer) {
    int rgb[3] = { 0xFF, 0xFF, 0xFF }; // values of white to be removed from main image
    // load main image (logo)
    if (!main_image.load_from_file(main_image_path, renderer, true, rgb)) {
        printf("Error loading menu's main image from %s!\n", main_image_path.c_str());
        printf("*** SDL_image Error: %s ***\n", IMG_GetError());
        exit(1);
    }
    else {
        // set flag
        is_main_image = true;
        // set dimensions
        mi_width = main_image.get_width();
        mi_height = main_image.get_height();
        // set location
        mi_x = (width / 2) - (main_image.get_width() / 2); // centered on x
        mi_y = 10; // 10px offset from boundary
    }
    // load background image
    if (!background.load_from_file(background_path, renderer)) {
        printf("Error loading menu's background from %s!\n", background_path.c_str());
        printf("*** SDL_image Error: %s ***\n", IMG_GetError());
        exit(1);
    }
    // set menu dimesions
    this->width = width;
    this->height = height;
    // set renderer
    m_renderer = renderer;
    // set last item location
    last_x = mi_x; last_y = mi_y + main_image.get_height();
}

Menu::Menu(int width, int height, SDL_Renderer* renderer) {
    // load background image
    if (!background.load_from_file(background_path, renderer)) {
        printf("Error loading menu's background from %s!\n", background_path.c_str());
        printf("*** SDL_image Error: %s ***\n", IMG_GetError());
        exit(1);
    }
    // set menu dimensions
    this->width = width;
    this->height = height;
    // set renderer
    m_renderer = renderer;
    // set last item location
    last_x = 0; last_y = 0;
}

Menu::~Menu() {
    // delete all menuItems
    for (unsigned i = 0; i < menu_items.size(); i++) {
        if (menu_items[i] != NULL) { delete menu_items[i]; }
    }
    // free textures
    main_image.free();
    background.free();
    // set renderer to null (don't erase as app might need it)
    m_renderer = NULL;
}

void Menu::add_option(int width, int height, string texture_path) {
    // create menu item
    MenuItem* new_option = new MenuItem(texture_path, m_renderer, width, height);
    // set new location based on last item
    int new_x = (this->width / 2) - (new_option->get_texture_width() / 2);
    int new_y = last_y + 10; // add 10px offset

    new_option->set_position(new_x, new_y);

    // update last location
    last_x = new_x; last_y = new_y + new_option->get_texture_height();

    menu_items.push_back(new_option);
}

void Menu::set_main_image_dim(int width, int height) {
    this->mi_width = width;
    this->mi_height = height;
    // reset location
    this->mi_x = (this->width / 2) - (mi_width / 2);
    this->mi_y = 10;
    // reset last location
    this->last_x = mi_x;
    this->last_y = mi_y + height;
}

void Menu::render_main_image() {
    // used to change location and size of render texture
    SDL_Rect renderQuad = { mi_x, mi_y, mi_width, mi_height };
    main_image.render(mi_x, mi_y, m_renderer, NULL, &renderQuad);
}

int Menu::handle_event(SDL_Event* e) {
    // make all items handle the event
    for (unsigned i = 0; i < menu_items.size(); i++) {
        if (menu_items[i]->handle_event(e)) {
            return i;
        }
    }
    return -1;
}

void Menu::render_items() {
    // render all menu items with their given specifications
    for (unsigned i = 0; i < menu_items.size(); i++) {
        SDL_Rect renderQuad = { menu_items[i]->get_x(),
                                menu_items[i]->get_y(),
                                menu_items[i]->get_texture_width(),
                                menu_items[i]->get_texture_height() };
        menu_items[i]->render(NULL, &renderQuad);
    }
}

void Menu::render() {
    background.render(x, y, m_renderer);
    if (is_main_image) { render_main_image(); }
    render_items();
}
