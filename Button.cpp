#include "Button.h"

void Button::setPosition(int x, int y) {
   position.x = x;
   position.y = y; 
}
SDL_Point Button::getPosition() {
   return position;
}

bool Button::isPressed(int mx, int my) {
   //check if mouse is over button
   if ((mx > position.x) &&
       (mx < (position.x + SIZE)) &&
       (my > position.y) && 
       (my < (position.y + SIZE))) {
         return true;
    }

    return false;      
}