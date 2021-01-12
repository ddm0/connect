#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

class Button {
    public:
        static const int SIZE = 80;
        void setPosition(int x, int y);
        SDL_Point getPosition();
        bool isPressed(int mx, int my);

    private:
        SDL_Point position;
};

#endif