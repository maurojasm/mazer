#include "../include/maze.h"

Maze::Maze(int size) {
    m_size = size;
    hex_maze = generate_hex_maze(size);
    map_maze = generate_map_maze(hex_maze, m_size);
}

string Maze::generate_hex_maze(int size) {
    return maze_generator.generate_maze(size);
}

bool Maze::has_char(char cell, char arr[]) {
    int size = sizeof(&arr) / sizeof(char) - 1;
    for(int i = 0; i < size; i++) {
        if(cell == arr[i]) {return true;}
    }
    return false;
}

string Maze::remove_dbl_walls(string maze, int size) {
    for(int i = 0; i < (size * size) - 1; i ++) {
        if(has_right_wall(maze[i + 1]) && ((i + 1) % size != 0)) {
            maze[i] -= 1;
        }
    }
    for(int i = 0; i < (size * size) - size; i++) {
        if(has_top_wall(maze[i + size])) {
            if(maze[i] == 'a') {
                maze[i] = '8';
            } else if (maze[i] == 'b') {
                maze[i] = '9';
            } else {
                maze[i] -= 2;
            }
        }
        
    }
    return maze;
}

string Maze::fill_wall(string map, int size) {
    size *= 4;
    for(int i = size; i < (size*size) - size; i++) {
        if(map[i] == '1' && map[i + 1] == '0' && map[i - size + 1] == '1' && map[i - size] == '0') {
            map[i + 1] = '1';
        }
    }

    return map;
}

string Maze::generate_map_maze(string maze, int size) {
    string map = "", row = "";

    maze = remove_dbl_walls(maze, size);
    // iterate through the maze
    for(int i = 0; i < size*size; i += size) {
        // get row
        row = maze.substr(i, size);
        // add section of cell to map
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
    map = fill_wall(map, size);
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