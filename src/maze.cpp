#include "../include/maze.h"

Maze::Maze(int size) {
    m_size = size;
    hex_maze = generate_hex_maze(size);
    map_maze = generate_map_maze(hex_maze, m_size);
}

string Maze::generate_hex_maze(int size) {
    return maze_generator.generate_maze(size);
}

string Maze::generate_map_maze(string maze, int size) {
    string map = "", row = "";
    // iterate through the maze
    for(int i = 0; i < size*size; i += size) {
        // get row
        row = maze.substr(i, size);
        // 
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < size; k++) {
                char hex = row[k];
                switch (hex) {
                case '0':
                    map += tile_0[j];
                    break;
                case '1':
                    map += tile_1[j];
                    break;
                case '2':
                    map += tile_2[j];
                    break;
                case '3':
                    map += tile_3[j];
                    break;
                case '4':
                    map += tile_4[j];
                    break;
                case '5':
                    map += tile_5[j];
                    break;
                case '6':
                    map += tile_6[j];
                    break;
                case '7':
                    map += tile_7[j];
                    break;
                case '8':
                    map += tile_8[j];
                    break;
                case '9':
                    map += tile_9[j];
                    break;
                case 'a':
                    map += tile_a[j];
                    break;
                case 'b':
                    map += tile_b[j];
                    break;
                case 'c':
                    map += tile_c[j];
                    break;
                case 'd':
                    map += tile_d[j];
                    break;
                case 'e':
                    map += tile_e[j];
                    break;
                }
            }
        }
    }
    return map;
}

string Maze::get_maze() {
    return hex_maze;
}

string Maze::get_map() {
    return map_maze;
}

int Maze::get_size() {
    return m_size;
}