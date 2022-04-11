// Copyright 2021 Alexander Lay-Calvert
#include "portal.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    // ncurses initialization
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    curs_set(0);

    // damn that sucks
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support colors\n");
        exit(1);
    }

    // initializing some colors
    start_color();
    use_default_colors();
    init_pair(EMPTY_COLOR_PAIR, COLOR_WHITE, COLOR_WHITE);
    init_pair(WALL_COLOR_PAIR, COLOR_WHITE, COLOR_WHITE);
    init_pair(PLAYER_COLOR_PAIR, COLOR_GREEN, COLOR_GREEN);
    init_pair(BLUE_PORTAL_COLOR_PAIR, COLOR_BLUE, COLOR_BLUE);
    init_pair(ORANGE_PORTAL_COLOR_PAIR, COLOR_RED, COLOR_RED);

    // getting terminal size info
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    char **grid = init_grid(rows, cols);

    char empty_row[cols];
    for (int i = 0; i < cols; i++) empty_row[i] = EMPTY;

    Direction look_dir = UP;
    int player_row = rows / 2;
    int player_col = cols / 2;

    CurrentPortal curr_portal = BLUE;
    int blue_portal_row = -1;
    int blue_portal_col = -1;
    int orange_portal_row = -1;
    int orange_portal_col = -1;
    bool blue_portal_set = false;
    bool orange_portal_set = false;

    /* TODO */
    // refactor
    // add features/levels

    // the game loop
    char move;
    do {
        switch (look_dir) {
            case UP:
                if (player_row - 1 > 0)
                    grid[player_row - 1][player_col] = LOOK_UP;
                break;
            case DOWN:
                if (player_row + 1 < rows - 1)
                    grid[player_row + 1][player_col] = LOOK_DOWN;
                break;
            case LEFT:
                if (player_col - 1 > 0)
                    grid[player_row][player_col - 1] = LOOK_LEFT;
                break;
            case RIGHT:
                if (player_col + 1 < cols - 1)
                    grid[player_row][player_col + 1] = LOOK_RIGHT;
                break;
            default:
                break;
        }
        if (blue_portal_set)
            grid[blue_portal_row][blue_portal_col] = BLUE_PORTAL;
        if (orange_portal_set)
            grid[orange_portal_row][orange_portal_col] = ORANGE_PORTAL;
        grid[player_row][player_col] = PLAYER;
        print_grid(rows, cols, grid);
        move(0, 0);
        move = getch();
        grid[player_row][player_col] = EMPTY;
        switch (look_dir) {
            case UP:
                if (player_row - 1 <= 0)
                    grid[player_row - 1][player_col] = WALL;
                else
                    grid[player_row - 1][player_col] = EMPTY;
                break;
            case DOWN:
                if (player_row + 1 >= rows - 1)
                    grid[player_row + 1][player_col] = WALL;
                else
                    grid[player_row + 1][player_col] = EMPTY;
                break;
            case LEFT:
                if (player_col - 1 <= 0)
                    grid[player_row][player_col - 1] = WALL;
                else
                    grid[player_row][player_col - 1] = EMPTY;
                break;
            case RIGHT:
                if (player_col + 1 >= cols - 1)
                    grid[player_row][player_col + 1] = WALL;
                else
                    grid[player_row][player_col + 1] = EMPTY;
                break;
            default:
                break;
        }
        switch (move) {
            case LOOK_UP_KEY:
                look_dir = UP;
                break;
            case LOOK_DOWN_KEY:
                look_dir = DOWN;
                break;
            case LOOK_LEFT_KEY:
                look_dir = LEFT;
                break;
            case LOOK_RIGHT_KEY:
                look_dir = RIGHT;
                break;
            case MOVE_UP_KEY:
                if (player_row - 1 > 0) player_row--;
                break;
            case MOVE_DOWN_KEY:
                if (player_row + 1 < rows - 1) player_row++;
                break;
            case MOVE_LEFT_KEY:
                if (player_col - 1 > 0) player_col--;
                break;
            case MOVE_RIGHT_KEY:
                if (player_col + 1 < cols - 1) player_col++;
                break;
            case TOGGLE_CURR_PORTAL_KEY:
                if (curr_portal == BLUE)
                    curr_portal = ORANGE;
                else
                    curr_portal = BLUE;
                break;
            case SHOOT_PORTAL_KEY:
                if (blue_portal_row > 0 && blue_portal_col > 0 &&
                    curr_portal == BLUE)
                    grid[blue_portal_row][blue_portal_col] = EMPTY;
                if (orange_portal_row > 0 && orange_portal_col > 0 &&
                    curr_portal == ORANGE)
                    grid[orange_portal_row][orange_portal_col] = EMPTY;
                int tmp_portal_row = -1;
                int tmp_portal_col = -1;
                switch (look_dir) {
                    case UP:
                        if (player_row - 1 == 0) break;
                        tmp_portal_row = player_row - 1;
                        tmp_portal_col = player_col;
                        while (grid[tmp_portal_row - 1][tmp_portal_col] ==
                               EMPTY)
                            tmp_portal_row--;
                        break;
                    case DOWN:
                        if (player_row + 1 == rows - 1) break;
                        tmp_portal_row = player_row + 1;
                        tmp_portal_col = player_col;
                        while (grid[tmp_portal_row + 1][tmp_portal_col] ==
                               EMPTY)
                            tmp_portal_row++;
                        break;
                    case LEFT:
                        if (player_col - 1 == 0) break;
                        tmp_portal_col = player_col - 1;
                        tmp_portal_row = player_row;
                        while (grid[tmp_portal_row][tmp_portal_col - 1] ==
                               EMPTY)
                            tmp_portal_col--;
                        break;
                    case RIGHT:
                        if (player_col + 1 == cols - 1) break;
                        tmp_portal_col = player_col + 1;
                        tmp_portal_row = player_row;
                        while (grid[tmp_portal_row][tmp_portal_col + 1] ==
                               EMPTY)
                            tmp_portal_col++;
                        break;
                    default:
                        break;
                }
                if (tmp_portal_row < 0 || tmp_portal_col < 0) break;
                if (curr_portal == BLUE) {
                    blue_portal_row = tmp_portal_row;
                    blue_portal_col = tmp_portal_col;
                    blue_portal_set = true;
                } else {
                    orange_portal_row = tmp_portal_row;
                    orange_portal_col = tmp_portal_col;
                    orange_portal_set = true;
                }
                break;
        }
        if (player_row == blue_portal_row && player_col == blue_portal_col) {
            if (orange_portal_set) {
                player_row = orange_portal_row;
                player_col = orange_portal_col;
            }
        } else if (player_row == orange_portal_row &&
                   player_col == orange_portal_col) {
            if (blue_portal_set) {
                player_row = blue_portal_row;
                player_col = blue_portal_col;
            }
        }
    } while (move != QUIT_KEY);
    endwin();
}

char **init_grid(const int rows, const int cols) {
    // Initialize the grid in memory
    char **grid = malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; ++i) {
        // Create each row
        grid[i] = malloc(sizeof(char) * cols);
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) grid[i][j] = EMPTY;
    for (int i = 0; i < rows; i++) {
        grid[i][0] = WALL;
        grid[i][cols - 1] = WALL;
    }
    for (int i = 0; i < cols; i++) {
        grid[0][i] = WALL;
        grid[rows - 1][i] = WALL;
    }

    return grid;
}

void print_grid(const int rows, const int cols, char **grid) {
    for (int i = 0; i < rows; i++) mvprintw(i, 0, "%s", grid[i]);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            attron(A_BOLD);
            if (grid[i][j] == PLAYER) {
                attron(COLOR_PAIR(PLAYER_COLOR_PAIR));
                mvprintw(i, j, "%c", grid[i][j]);
                attroff(COLOR_PAIR(PLAYER_COLOR_PAIR));
            } else if (grid[i][j] == WALL) {
                attron(COLOR_PAIR(WALL_COLOR_PAIR));
                mvprintw(i, j, "%c", grid[i][j]);
                attroff(COLOR_PAIR(WALL_COLOR_PAIR));
            } else if (grid[i][j] == BLUE_PORTAL) {
                attron(COLOR_PAIR(BLUE_PORTAL_COLOR_PAIR));
                mvprintw(i, j, "%c", PORTAL);
                attroff(COLOR_PAIR(BLUE_PORTAL_COLOR_PAIR));
            } else if (grid[i][j] == ORANGE_PORTAL) {
                attron(COLOR_PAIR(ORANGE_PORTAL_COLOR_PAIR));
                mvprintw(i, j, "%c", PORTAL);
                attroff(COLOR_PAIR(ORANGE_PORTAL_COLOR_PAIR));
            } else {
                mvprintw(i, j, "%c", grid[i][j]);
            }
            attroff(A_BOLD);
        }
    }
}
