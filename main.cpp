#include <iostream>
#include "Window.h"
#include "Graphics.h"
#include "Board.h"

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

void g() {

}

void gridToPosition(int *x, int *y) {
    *x = WINDOW_WIDTH + board.CELL_SIZE * (*x + 1);
    *y = WINDOW_HEIGHT + board.CELL_SIZE * (*y + 1);
}

void updateWindow(std::vector<CellData> changelist) {
    int x, y;
    window.addTexture(graphics.getTexture(BOARD), board_rect);

    for (std::vector<CellData>::iterator it = changelist.begin(); it != changelist.end(); ++it) {
        x = it->x;
        y = it->y;
        gridToPosition(&x, &y);

        SDL_Rect r{x, y, board.CELL_SIZE, board.CELL_SIZE};
        window.addTexture(graphics.getTexture(it->s), r);
    }

    window.display();
}

int main(int argc, const char* argv[]) {
    int mousex;
    int mousey;
    bool exit = false;
    SDL_Event e;
    
    const std::string BOARD_PATH = "board.png";
    const std::string RED_PATH = "sprite.png";
    const std::string BLUE_PATH = "sprite.png";
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
                        updateWindow(board.changelist);
                    }
                    break;
            }
        }
    }
    
    graphics.close();
    window.close();
    return 0;
}