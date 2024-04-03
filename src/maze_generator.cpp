#include <stdio.h>
#include <string>
#include <ctime>

#include "../include/maze_generator.h"

Maze_Gen::Maze_Gen() {
    std::srand(std::time(0));
}

string Maze_Gen::generate_maze(int size) {
    int index = 0, m_size = 0;
    
    if (size == 5) {
        m_size = easy_collection.size();
    } else if(size == 8) {
        m_size = mid_collection.size();
    } else {
        m_size = hard_collection.size();
    }
    // for some reason calling rand once gets 5 all the time
    for(int i = 0; i < 3; i++) {
        index = rand()%m_size;
        // printf("%d\n", index);
    }
    string maze = easy_collection[index];

    return maze;
}