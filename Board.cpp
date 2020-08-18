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
    changelist.clear();

    int mx;
    int my; 
    SDL_GetMouseState(&mx, &my);
    std::cout << "mx: " << mx << " my: " << my;

    for (int i = 0; i < BUTTONS; i++) {
        if (button[i].isPressed(mx,my)) {
            push(button[i]);
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
    changelist.push_back(CellData{x, y, s});
    grid[x][y] = s;
}

void Board::push(Button b) {
    //get grid position of button
    int x, y;
    getGridPosition(b, &x, &y);

    //determine button type from grid position
    //getButtonType(grid_x, grid_y);


    //push down
    if (0 < x < 8 && y == 0) {
        x--;
        y--;
       
       
        int i = 0;
        for ( ; i < 6; i++) {
            if (grid[x][i] != EMPTY) {
               break; 
            }
        }
        
        for ( ; i > 0; i--) {
            //grid[x][i] = grid[x][i-1];
            setCell(x, i, grid[x][i-1]);
        }

        //grid[x][0] = RED;
        setCell(x, 0, RED_CELL);
    }
   /* 
    //push up
    else if (0 < x < 8 && y == 8)

    //push right
    else if (x == 0 && 0 < y < 8)

    //push left
    else if (x == 8 && 0 < y < 8)

    //push bottom right
    else if (x == 0 && y == 0) 

    //push bottom left
    else if (x == 8 && y == 0) 

    //push top right
    else if (x == 0 && y == 8) 

    //push top left
    else if (x == 8 && y == 8) 
    */
    


    //add piece and shift if necessary
}