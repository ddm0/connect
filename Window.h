#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window {
    public:
        Window(int width, int height);
        void close();
        void display();
        SDL_Renderer* getRenderer();
        void addTexture(SDL_Texture *texture, SDL_Rect &rect);
    private:
        SDL_Window *window;
        SDL_Surface *screen;
        SDL_Renderer *renderer;
};

#endif