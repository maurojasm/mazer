#include "../include/menu.h"

Menu::Menu(string main_image_path, int m_width, int m_height, SDL_Renderer* renderer) {
    // set menu dimesions
    this->m_width = m_width;
    this->m_height = m_height;
    // set renderer
    m_renderer = renderer;

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
        set_main_image_dim(main_image.get_width(), main_image.get_height());
    }
    // load background image
    if (!background.load_from_file(background_path, renderer)) {
        printf("Error loading menu's background from %s!\n", background_path.c_str());
        printf("*** SDL_image Error: %s ***\n", IMG_GetError());
        exit(1);
    }
}

Menu::Menu(int m_width, int m_height, SDL_Renderer* renderer) {
    // load background image
    if (!background.load_from_file(background_path, renderer)) {
        printf("Error loading menu's background from %s!\n", background_path.c_str());
        printf("*** SDL_image Error: %s ***\n", IMG_GetError());
        exit(1);
    }
    // set menu dimensions
    this->m_width = m_width;
    this->m_height = m_height;
    // set renderer
    m_renderer = renderer;
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
    // added to list of menu items
    menu_items.push_back(new_option);
    // rearrage all items in the menu to center them
    rearrange_items();
}

void Menu::rearrange_items() {
    // total height of all items and offsets
    unsigned total_height = 0;
    // if we have a main image add it's height
    if (is_main_image) {
        total_height += mi_height;
    }
    // add height offset and item height to total height
    for (unsigned i = 0; i < menu_items.size(); i++) {
        total_height += h_offset + menu_items[i]->get_texture_height();
    }
    // set main image location
    mi_x = (m_width / 2) - (mi_width / 2);
    mi_y = (m_height / 2) - (total_height / 2);
    // record end of main image
    unsigned last_y = mi_y + mi_height;
    // reset all items positions
    for (unsigned j = 0; j < menu_items.size(); j++) {
        last_y += h_offset;
        menu_items[j]->set_position((m_width / 2) - (menu_items[j]->get_texture_width() / 2), last_y);
        last_y += menu_items[j]->get_texture_height();
    }
}

void Menu::set_main_image_dim(int new_width, int new_height) {
    this->mi_width = new_width;
    this->mi_height = new_height;
    // reset all items locations
    rearrange_items();
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
    SDL_Rect renderQuad = { m_x, m_y, m_width, m_height };
    background.render(m_x, m_y, m_renderer, NULL, &renderQuad);
    if (is_main_image) { render_main_image(); }
    render_items();
}
