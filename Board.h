#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "Button.h"
#include <iostream>
#include <vector>


enum cell_state {EMPTY = 0, RED_CELL = 1, BLUE_CELL = 2};
struct CellData {int x; int y; cell_state s;};

class Board {
    public:
        static const int BUTTONS = 32;
        static const int CELL_SIZE = 80;
        static const int BOARD_SIZE = 7;
        Board(int x, int y);
        std::vector<CellData> changelist;
        bool handleEvent(SDL_Event* e);
        void setPosition(int x, int y);
    
    private:
        SDL_Point position;
        cell_state grid[BOARD_SIZE][BOARD_SIZE];
        Button button[BUTTONS];
        void getGridPosition(Button b, int *x, int *y);
        void setCell(int x, int y, cell_state s);
        void push(Button b);

};

#endif