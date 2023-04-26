//
//  i_controller.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_controller_hpp
#define i_controller_hpp

class game_model;

#include <SDL2/SDL.h>

class i_controller {
    
public:
    i_controller(game_model * model): model(model) { }
    
    virtual void handle_input() = 0;
    
    virtual void key_pressed(SDL_Keysym key) = 0;
    virtual void key_unpressed(SDL_Keysym key) = 0;
    
protected:
    
    game_model * model;
};

#endif /* i_controller_hpp */
