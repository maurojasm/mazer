#include "../include/maze.h"

Maze::Maze(int size) {
    m_size = size;
    // get random hex maze
    hex_maze = generate_hex_maze(size);
    // generate map from hex maze
    map_maze = generate_map_maze(hex_maze, m_size);
}

string Maze::generate_hex_maze(int size) {
    return maze_generator.generate_maze(size);
}

bool Maze::has_char(char cell, char arr[]) {
    int size = sizeof(&arr) / sizeof(char) - 1;
    for (int i = 0; i < size; i++) {
        if (cell == arr[i]) { return true; }
    }
    return false;
}

string Maze::remove_dbl_walls(string maze, int size) {
    // remove right wall
    for (int i = 0; i < (size * size) - 1; i++) {
        if (has_right_wall(maze[i + 1]) && ((i + 1) % size != 0)) {
            maze[i] -= 1;
        }
    }
    // remove lower wall
    for (int i = 0; i < (size * size) - size; i++) {
        if (has_top_wall(maze[i + size])) {
            if (maze[i] == 'a') {
                maze[i] = '8';
            }
            else if (maze[i] == 'b') {
                maze[i] = '9';
            }
            else {
                maze[i] -= 2;
            }
        }

    }
    return maze;
}

string Maze::fill_wall(string map, int size) {
    size *= 4;
    // look for pattern
    for (int i = size; i < (size * size) - size; i++) {
        if (map[i] == '1' && map[i + 1] == '0' && map[i - size + 1] == '1' && map[i - size] == '0') {
            map[i + 1] = '1';
        }
    }

    return map;
}

string Maze::generate_map_maze(string maze, int size) {
    string map = "", row = "";

    maze = remove_dbl_walls(maze, size);
    // iterate through the maze
    for (int i = 0; i < size * size; i += size) {
        // get row
        row = maze.substr(i, size);
        // add section of cell to map
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < size; k++) {
                char hex = row[k];
                switch (hex) {
                case '0':
                    map += cell_0[j];
                    break;
                case '1':
                    map += cell_1[j];
                    break;
                case '2':
                    map += cell_2[j];
                    break;
                case '3':
                    map += cell_3[j];
                    break;
                case '4':
                    map += cell_4[j];
                    break;
                case '5':
                    map += cell_5[j];
                    break;
                case '6':
                    map += cell_6[j];
                    break;
                case '7':
                    map += cell_7[j];
                    break;
                case '8':
                    map += cell_8[j];
                    break;
                case '9':
                    map += cell_9[j];
                    break;
                case 'a':
                    map += cell_a[j];
                    break;
                case 'b':
                    map += cell_b[j];
                    break;
                case 'c':
                    map += cell_c[j];
                    break;
                case 'd':
                    map += cell_d[j];
                    break;
                case 'e':
                    map += cell_e[j];
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