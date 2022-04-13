#ifndef PORTAL_H_
#define PORTAL_H_

#define WALL_C 'I'
#define PLAYER_C 'X' // TODO
#define EMPTY_C ' '

#define BLUE_PORTAL_C 'B'   // TODO
#define ORANGE_PORTAL_C 'R' // TODO
#define PORTAL_C 'O'        // TODO
#define HOLD_BUTTON_C 'H'   // TODO
#define BLOCK_C 'C'         // TODO
#define LEVER_ON_C 'L'      // TODO
#define LEVER_OFF_C 'l'     // TODO
#define KEY_C 'K'           // TODO
#define END_C 'E'           // TODO
#define F_REFLECTOR_C '/'   // TODO
#define B_REFLECTOR_C '\\'  // TODO

#define QUIT_KEY 'q'

#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'
#define SHOOT_PORTAL ' '
#define TOGGLE_PORTAL '\t'

#define MENU_SELECTED_COLOR_PAIR 1
#define MENU_BORDER_COLOR_PAIR 2
#define EMPTY_COLOR_PAIR 3
#define WALL_COLOR_PAIR 4
#define PLAYER_COLOR_PAIR 5
#define BPORTAL_COLOR_PAIR 6
#define OPORTAL_COLOR_PAIR 7
#define HOLD_BUTTON_COLOR_PAIR 8
#define BLOCK_COLOR_PAIR 9
#define LEVER_ON_COLOR_PAIR 10
#define LEVER_OFF_COLOR_PAIR 11
#define KEY_COLOR_PAIR 12
#define END_COLOR_PAIR 13

#define LOOK_UP '^'
#define LOOK_DOWN 'v'
#define LOOK_LEFT '<'
#define LOOK_RIGHT '>'

typedef enum node_type {
    PLAYER,
    BLUE_PORTAL,
    ORANGE_PORTAL,
    WALL,
    EMPTY,
    END,
    BLOCK,
    HOLD_BUTTON,
    LEVER_ON,
    LEVER_OFF,
    KEY,
    F_REFLECTOR,
    B_REFLECTOR
} NodeType;
typedef struct node {
    int row;
    int col;
    char ch;
    NodeType type;
} Node;
typedef enum direction { UP, DOWN, LEFT, RIGHT } Direction;
typedef enum current_portal { BLUE, ORANGE } CurrentPortal;

void init_map(const int rows, const int cols);
void destroy_map();
void print_map();
void update();
void play();
void move_player(Direction dir);

#endif // PORTAL_H_
