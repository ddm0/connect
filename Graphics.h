#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

class Graphics {
    public:
        int createTexture(std::string path, SDL_Renderer* renderer);
        SDL_Texture* getTexture(int i);
        //SDL_Texture* getTexture();
        SDL_Texture* getLastTexture();
        void close();
    private:
        std::vector<SDL_Surface*> image;
        std::vector<SDL_Texture*> texture;
};

#endif