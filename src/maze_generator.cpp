#include <ctime>

#include "../include/maze_generator.h"

Maze_Gen::Maze_Gen() {
    // seed time 
    std::srand(std::time(0));
}

int get_rand(int n) {
    int x = 0;
    // for some reason calling rand once gets 5 all the time
    for (int i = 0; i < 3; i++) {
        x = rand() % n;
    }
    return x;
}

string Maze_Gen::generate_maze(int size) {
    string maze = "";

    switch (size) {
    case 5: // easy
        maze = easy_collection[get_rand(easy_collection.size())];
        break;
    case 8: // medium
        maze = mid_collection[get_rand(mid_collection.size())];
        break;
    case 10: // hard
        maze = hard_collection[get_rand(hard_collection.size())];
        break;
    default: // default is easy
        maze = easy_collection[get_rand(easy_collection.size())];
        break;
    }

    return maze;
}