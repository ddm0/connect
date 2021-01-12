#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "Button.h"
#include <iostream>
#include <vector>
#include <array>

enum cell_state {EMPTY = 0, RED_CELL = 1, BLUE_CELL = 2};
struct CellData {int x; int y; cell_state s;};

class Board {
    public:
        static const int BUTTONS = 32;
        static const int CELL_SIZE = 80;
        static const int BOARD_SIZE = 7;
        Board(int x, int y);
        bool handleEvent(SDL_Event* e);
        void setPosition(int x, int y);
        std::array<std::array<cell_state, 7>, 7> getGrid();
        cell_state next_cell = RED_CELL; //crashes if private
    
    private:
        SDL_Point position;
        std::array<std::array<cell_state, 7>, 7> grid;
        Button button[BUTTONS];
        bool gameover;
        void getGridPosition(Button b, int *x, int *y);
        void setCell(int x, int y, cell_state s);
        void pushUp(int x);
        void pushLeft(int y);
        void pushRight(int y);
        void pushDown(int x);
        void pushDownRight();
        void pushDownLeft();
        void pushUpRight();
        void pushUpLeft();
        void push(Button b);
        void updateGameState();

};

#endif