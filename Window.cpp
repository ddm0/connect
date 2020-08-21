#include "Window.h"

Window::Window(int width, int height) {

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("SDL Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(
        "Connect 4",                  
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        width,                               // width, in pixels
        height,                               // height, in pixels
        SDL_WINDOW_SHOWN                  // flags - see below
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    screen = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Window::close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void Window::clear() {
    SDL_RenderClear(renderer);
}

void Window::display() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer() {
    return renderer;
}

void Window::addTexture(SDL_Texture *texture, SDL_Rect &rect) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

/*
int loadImage(std::string path){
    image = SDL_LoadBMP(path.c_str());
    if ( image == NULL ) {
        printf("Image failed to load: %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}
*/