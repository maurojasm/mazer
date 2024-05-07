#ifndef MAZE_H
#define MAZE_H

#include <string>

#include "maze_generator.h"

using std::string;

/*
Holds one random maze, but can generate random mazes as well
*/
class Maze {
public:
    /*
    Constructor - set the maze of the given size and creates a map of it.

    @param size size of maze to hold
    */
    Maze(int size = 5);

    /*
    Generates random maze in hex format. Default size is 5.

    @param size size of maze to generate
    @return     maze in hex format
    */
    string generate_hex_maze(int size = 5);

    /*
    Generates a map of a given maze in hex format into binary format.

    @param maze maze in hex format
    @param size size of the hex maze
    @return     map of given maze
    */
    string generate_map_maze(string maze, int size);

    /*
    @return object's hex maze.
    */
    string get_maze();

    /*
    @return object's maze map.
    */
    string get_map();

    /*
    @return object's maze size.
    */
    int get_size();

private:
    // generator of maze in hexadecimal format
    Maze_Gen maze_generator;

    /*
    Checks if current char is in the array.

    @param cell character to find in array
    @param arr  character arr to look into
    @return     true if cell was found
    */
    bool has_char(char cell, char arr[]);

    /*
    Checks if cell has a right wall.

    @param cell cell to check
    @return     true if cell was found
    */
    bool has_right_wall(char cell) { return has_char(cell, has_right); }

    /*
    Checks if cell has a top wall.

    @param cell cell to check
    @return     true if cell was found
    */
    bool has_top_wall(char cell) { return has_char(cell, has_top); }

    /*
    Removes double walls from a hex maze.

    @param maze hex maze to remove the walls
    @param size size of maze
    @return     hex maze without double walls
    */
    string remove_dbl_walls(string maze, int size);

    /*
    Fill in corners of walls after removing double walls.

    @param map  map of the maze
    @param size size of the maze
    @return     map of maze with cornes filled
    */
    string fill_wall(string map, int size);

    // hex maze
    string hex_maze;

    // map of hex maze
    string map_maze;

    // maze size
    int m_size;

    // cells that have a right wall
    char has_right[7] = { '4', '5', '6', '7', 'c', 'd', 'e' };

    // cells that have a top wall
    char has_top[7] = { '8', '9', 'a', 'b', 'c', 'd', 'e' };

    // maze cell to map
    string
        cell_0[4] = { "0000",
                    "0000",
                    "0000",
                    "0000" },
        cell_1[4] = { "0001",
                    "0001",
                    "0001",
                    "0001" },
        cell_2[4] = { "0000",
                    "0000",
                    "0000",
                    "1111" },
        cell_3[4] = { "0001",
                    "0001",
                    "0001",
                    "1111" },
        cell_4[4] = { "1000",
                    "1000",
                    "1000",
                    "1000" },
        cell_5[4] = { "1001",
                    "1001",
                    "1001",
                    "1001" },
        cell_6[4] = { "1000",
                    "1000",
                    "1000",
                    "1111" },
        cell_7[4] = { "1001",
                    "1001",
                    "1001",
                    "1111" },
        cell_8[4] = { "1111",
                    "0000",
                    "0000",
                    "0000" },
        cell_9[4] = { "1111",
                    "0001",
                    "0001",
                    "0001" },
        cell_a[4] = { "1111",
                    "0000",
                    "0000",
                    "1111" },
        cell_b[4] = { "1111",
                    "0001",
                    "0001",
                    "1111" },
        cell_c[4] = { "1111",
                    "1000",
                    "1000",
                    "1000" },
        cell_d[4] = { "1111",
                    "1001",
                    "1001",
                    "1001" },
        cell_e[4] = { "1111",
                    "1000",
                    "1000",
                    "1111" };
};

#endif