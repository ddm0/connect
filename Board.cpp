#include "Board.h"

Board::Board(int x, int y) {
    position.x = x;
    position.y = y;

    int point = 0;

    //top and bottom buttons
    for (int i = 0; i < 7; i++) {
        button[point].setPosition((x + CELL_SIZE) + (i * CELL_SIZE), y);
        point++;
        button[point].setPosition((x + CELL_SIZE) + (i * CELL_SIZE), y + (CELL_SIZE * 8));
        point++;
    } 

    //left, right, and corner buttons 
    for (int i = 0; i < 10; i++) {
        button[point].setPosition(x, y + (i * CELL_SIZE));
        point++;
        button[point].setPosition(x + (CELL_SIZE * 8), y + (i * CELL_SIZE));
        point++;
    }
}

bool Board::handleEvent(SDL_Event* e) {
    int mx;
    int my; 
    SDL_GetMouseState(&mx, &my);

    for (int i = 0; i < BUTTONS; i++) {
        if (button[i].isPressed(mx,my)) {
            push(button[i]);
            updateGameState();
            return true;
        }
    }

    return false;
}

void Board::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Board::getGridPosition(Button b, int *x, int *y) {
    SDL_Point b_pos = b.getPosition();
    *x = (b_pos.x - position.x) / CELL_SIZE;
    *y = (b_pos.y - position.y) / CELL_SIZE;
}

void Board::setCell(int x, int y, cell_state s) {
    grid[x][y] = s;
}
        
std::array<std::array<cell_state, 7>, 7> Board::getGrid() {
    return grid;
}

void Board::pushDown(int x) {
    int i = 0;

    for ( ; i < 6; i++) {
        if (grid[x][i] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i > 0; i--) {
        setCell(x, i, grid[x][i-1]);
    }

    setCell(x, 0, next_cell);
}

void Board::pushUp(int x) {
    int i = 6;

    for ( ; i > 0; i--) {
        if (grid[x][i] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i < 6; i++) {
        setCell(x, i, grid[x][i+1]);
    }

    setCell(x, 6, next_cell);
}

void Board::pushRight(int y) {
    int i = 0;

    for ( ; i < 6; i++) {
        if (grid[i][y] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i > 0; i--) {
        setCell(i, y, grid[i-1][y]);
    }

    setCell(0, y, next_cell);
}

void Board::pushLeft(int y) {
    int i = 6;

    for ( ; i > 0; i--) {
        if (grid[i][y] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i < 6; i++) {
        setCell(i, y, grid[i+1][y]);
    }

    setCell(6, y, next_cell);
}

void Board::pushDownRight() {
    int i = 0;

    for ( ; i < 6; i++) {
        if (grid[i][i] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i > 0; i--) {
        setCell(i, i, grid[i-1][i-1]);
    }

    setCell(0, 0, next_cell);
}

void Board::pushDownLeft() {
    int i = 6;
    int j = 0;

    for ( ; i > 0; i--, j++) {
        if (grid[i][j] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i < 6; i++, j--) {
        setCell(i, j, grid[i+1][j-1]);
    }

    setCell(6, 0, next_cell);
}

void Board::pushUpRight() {
    int i = 0;
    int j = 6;

    for ( ; i < 6; i++, j--) {
        if (grid[i][j] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i > 0; i--, j++) {
        setCell(i, j, grid[i-1][j+1]);
    }

    setCell(0, 6, next_cell);
}

void Board::pushUpLeft() {
    int i = 6;

    for ( ; i > 0; i--) {
        if (grid[i][i] == EMPTY) {
            break; 
        }
    }
    
    for ( ; i < 6; i++) {
        setCell(i, i, grid[i+1][i+1]);
    }

    setCell(6, 6, next_cell);
}

void Board::push(Button b) {
    int x, y;
    getGridPosition(b, &x, &y);

    //each button coordinate must be adjusted to inner grid coordinates
    if (0 < x && x < 8 && y == 0) {
        pushDown(x - 1);
    } else if (0 < x && x < 8 && y == 8) {
        pushUp(x - 1);       
    } else if (x == 0 && 0 < y && y < 8) {
        pushRight(y - 1);
    } else if (x == 8 && 0 < y && y < 8) {
        pushLeft(y - 1);
    } else if (x == 0 && y == 0) {
        pushDownRight();
    } else if (x == 8 && y == 0) {
        pushDownLeft();
    } else if (x == 0 && y == 8) {
        pushUpRight();
    } else if (x == 8 && y == 8) {
        pushUpLeft();
    }
}

void Board::updateGameState() {
    if (next_cell == RED_CELL)
        next_cell = BLUE_CELL;
    else
        next_cell = RED_CELL;
    
}