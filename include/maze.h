#ifndef MAZE_H
#define MAZE_H

#include <string>

#include "maze_generator.h"

using std::string;

// holds one random maze, but can generate random mazes as well
class Maze {
    public:
        // constructor
        Maze(int size = 5);

        // generates random hex maze
        // default size is 5
        string generate_hex_maze(int size = 5);

        // generates map of given maze
        string generate_map_maze(string maze, int size);

        // get object's maze
        string get_maze();

        // get object's maze map
        string get_map();

        // get object's maze size
        int get_size();

    private:
        // generator of maze in hexadecimal format
        Maze_Gen maze_generator;

        // finds cell in array
        bool has_char(char cell, char arr[]);

        // checks if cell has right wall
        bool has_right_wall(char cell) { return has_char(cell, has_right); }

        // checks if cell has top wall
        bool has_top_wall(char cell) { return has_char(cell, has_top); }

        // removes double walls from the maze
        string remove_dbl_walls(string maze, int size);

        // fills corners after removing double walls
        string fill_wall(string map, int size);

        // hex maze
        string hex_maze;

        // map of hex maze
        string map_maze;

        // maze size
        int m_size;

        // cells that have a right wall
        char has_right[7] = {'4', '5', '6', '7', 'c', 'd', 'e'};

        // cells that have a top wall
        char has_top[7] = {'8', '9', 'a', 'b', 'c', 'd', 'e'};

        // maze tile to map
        string
        tile_0[4] = {"0000",
                    "0000",
                    "0000",
                    "0000"},
        tile_1[4] = {"0001",
                    "0001",
                    "0001",
                    "0001"},
        tile_2[4] = {"0000",
                    "0000",
                    "0000",
                    "1111"},
        tile_3[4] = {"0001",
                    "0001",
                    "0001",
                    "1111"},
        tile_4[4] = {"1000",
                    "1000",
                    "1000",
                    "1000"},
        tile_5[4] = {"1001",
                    "1001",
                    "1001",
                    "1001"},
        tile_6[4] = {"1000",
                    "1000",
                    "1000",
                    "1111"},
        tile_7[4] = {"1001",
                    "1001",
                    "1001",
                    "1111"},
        tile_8[4] = {"1111",
                    "0000",
                    "0000",
                    "0000"},
        tile_9[4] = {"1111",
                    "0001",
                    "0001",
                    "0001"},
        tile_a[4] = {"1111",
                    "0000",
                    "0000",
                    "1111"},
        tile_b[4] = {"1111",
                    "0001",
                    "0001",
                    "1111"},
        tile_c[4] = {"1111",
                    "1000",
                    "1000",
                    "1000"},
        tile_d[4] = {"1111",
                    "1001",
                    "1001",
                    "1001"},
        tile_e[4] = {"1111",
                    "1000",
                    "1000",
                    "1111"};
};

#endif