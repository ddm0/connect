#include <iostream>
#include "Window.h"
#include "Graphics.h"
#include "Board.h"

void gridToPosition(int *x, int *y);
void updateWindow(std::array<std::array<cell_state, 7>, 7> grid);

enum texture{BOARD = 0, RED = 1, BLUE = 2};
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int BOARD_X = WINDOW_WIDTH/2-WINDOW_HEIGHT/2;
const int BOARD_Y = 0;

Window window(WINDOW_WIDTH,WINDOW_HEIGHT); 
Graphics graphics;
Board board(BOARD_X,BOARD_Y);
SDL_Rect board_rect{BOARD_X,BOARD_Y,WINDOW_HEIGHT,WINDOW_HEIGHT};
SDL_Rect cell_rect{board.CELL_SIZE};

int main(int argc, const char* argv[]) {
    int mousex;
    int mousey;
    bool exit = false;
    SDL_Event e;
    
    const std::string BOARD_PATH = "board.png";
    const std::string RED_PATH = "red.png";
    const std::string BLUE_PATH = "blue.png";
    graphics.createTexture(BOARD_PATH, window.getRenderer());
    graphics.createTexture(RED_PATH, window.getRenderer());
    graphics.createTexture(BLUE_PATH, window.getRenderer());

    window.addTexture(graphics.getTexture(BOARD), board_rect);
    window.display();

    while(!exit){

        while(SDL_PollEvent ( &e ) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    exit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (board.handleEvent(&e)) {
                        updateWindow(board.getGrid());
                    }
                    break;
            }
        }
    }
    
    graphics.close();
    window.close();
    return 0;
}

void gridToPosition(int *x, int *y) {
    *x = BOARD_X + board.CELL_SIZE * (*x + 1);
    *y = BOARD_Y + board.CELL_SIZE * (*y + 1);
}

void updateWindow(std::array<std::array<cell_state, 7>, 7> grid) {
    int x, y;
    window.clear();
    window.addTexture(graphics.getTexture(BOARD), board_rect);
    
    for (int i = 0; i < board.BOARD_SIZE; i++) {
        for (int j = 0; j < board.BOARD_SIZE; j++) {
            if(grid[i][j] != EMPTY) {
                x = i;
                y = j;
                gridToPosition(&x, &y);
                SDL_Rect r{x, y, board.CELL_SIZE, board.CELL_SIZE};
                window.addTexture(graphics.getTexture(grid[i][j]), r);
            }
        }
    }
    
    window.display();
}