#include "../include/menuItem.h"

MenuItem::MenuItem(string path, SDL_Renderer* renderer, int width, int height) {
    item_renderer = renderer;
    if (!item_texture.load_from_file(path, renderer)) {
        printf("Unable to load menu item texture!\n");
        exit(1);
    }
    if (width == 0 || height == 0) {
        item_width = item_texture.get_width();
        item_height = item_texture.get_height();
    }
    else {
        item_width = width;
        item_height = height;
    }
}

MenuItem::~MenuItem() {
    item_texture.free();
    item_renderer = NULL;
}

void MenuItem::set_position(int x, int y) {
    this->x = x;
    this->y = y;
}

void MenuItem::set_dimesions(int width, int height) {
    this->item_width = width;
    this->item_height = height;
}

void MenuItem::render(SDL_Rect* clip, SDL_Rect* renderQuad) {
    item_texture.render(x, y, item_renderer, clip, renderQuad);
}

bool MenuItem::handle_event(SDL_Event* e) {
    // if mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int m_x, m_y;
        SDL_GetMouseState(&m_x, &m_y);

        // Check if mouse is inside button
        bool inside = false;
        if (((m_x > x) && (m_x < x + item_width)) && ((m_y > y) && (m_y < y + item_height))) {
            inside = true;
        }

        if (inside) { // change color to show interactivity
            item_texture.set_color(151, 35, 53);

            switch (e->type) { // if mouse inside and is pressed
            case SDL_MOUSEBUTTONDOWN:
                return true;
            }
        }
        // mouse not inside, revert to original color
        else { item_texture.set_color(255, 255, 255); }
    }
    return false;
}