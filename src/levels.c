#include "levels.h"
#include "portal_chars.h"

/*
 * Level 000: Lonely
 *
 * Objective: Nothing. There is nothing to do but shoot portals at walls.
 *
 * Strategy: Die alone.
 */
InitPosition init_level_000(const int rows, const int cols,
                            char grid[rows][cols]) {
    // add walls
    for (int i = 0; i < rows; i++) {
        grid[i][0] = WALL;
        grid[i][cols - 1] = WALL;
    }
    for (int i = 0; i < cols; i++) {
        grid[0][i] = WALL;
        grid[rows - 1][i] = WALL;
    }
    InitPosition init_pos;
    init_pos.row = rows / 2;
    init_pos.col = cols / 2;
    return init_pos;
}

/*
 * Level 001: Basic
 *
 * Objective: Reach the end point.
 *
 * Strategy: Come on dude
 */
InitPosition init_level_001(const int rows, const int cols,
                            char grid[rows][cols]) {
    // add walls
    for (int i = 0; i < rows; i++) {
        grid[i][0] = WALL;
        grid[i][cols - 1] = WALL;
    }
    for (int i = 0; i < cols; i++) {
        grid[0][i] = WALL;
        grid[rows - 1][i] = WALL;
    }
    grid[rows / 2][cols / 2] = END;
    grid[(rows / 2) - (rows / 4)][cols / 2] = F_REFLECTOR;
    InitPosition init_pos;
    init_pos.row = 2;
    init_pos.col = 2;
    return init_pos;
}
