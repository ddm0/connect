#include "Graphics.h"

int Graphics::createTexture(std::string path, SDL_Renderer* renderer) {
    image.push_back(IMG_Load(path.c_str()));
    
    if (image.back() == nullptr) {
        printf("Image failed to load: %s\n", IMG_GetError());
        return 1;
    }

    texture.push_back(SDL_CreateTextureFromSurface(renderer, image.back()));

    return 0;
}

SDL_Texture* Graphics::getTexture(int i) {
    return texture[i];
}
 
void Graphics::close() {
    for (unsigned i = 0; i < image.size(); i++) {
        SDL_FreeSurface(image[i]);
        image[i] = NULL;
    }

    for (unsigned i = 0; i < texture.size(); i++) {
        SDL_DestroyTexture(texture[i]);
    }
}

SDL_Texture* Graphics::getLastTexture() {
    return texture.back();
}