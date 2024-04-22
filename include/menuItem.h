#include "texture.h"
// #include <iostream>

using std::string;
/*
class item {
protected:
    int x;
    int y;
    int width;
    int height;

public:
    MenuItem(int x, int y, int width, int height);
    ~MenuItem();
    bool checkBounds(int posX, int posY);
};
*/
class MenuItem {
public:
    MenuItem(string path, SDL_Renderer* renderer, int width = 0, int height = 0);

    ~MenuItem();

    void set_position(int x, int y);

    void set_dimesions(int width, int height);

    bool handle_event(SDL_Event* e);

    void render(SDL_Rect* clip = NULL, SDL_Rect* renderQuad = NULL);

    int get_texture_width() { return item_width; }

    int get_texture_height() { return item_height; }

    int get_x() { return x; }
    int get_y() { return y; }

private:
    int item_width, item_height;
    int x = 0, y = 0;

    SDL_Renderer* item_renderer;

    Texture item_texture;
};