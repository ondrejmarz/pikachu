//
//  impl_controller.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef impl_controller_hpp
#define impl_controller_hpp

#include<set>

#include "i_controller.hpp"

class keyboard_handler;

class imp_controller: public i_controller {
    
public:
    imp_controller(game_model * model): i_controller(model) { }
    
    void handle_input( void );
    
    void key_pressed(SDL_Keysym key);
    void key_unpressed(SDL_Keysym key);
    
private:
    std::set<SDL_Keycode> key_state;
};

#endif /* impl_controller_hpp */
