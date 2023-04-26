//
//  impl_controller.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "impl_controller.hpp"
#include "../command/impl_command.hpp"
#include "../model/game_model.hpp"

void imp_controller::handle_input( void ) {
    
    //  0    1    2
    //
    //  3    4    5      (-4)
    //
    //  6    7    8
    
    int direction = 0;
    
    for (auto &e: key_state ) {
        
            switch (e) {
                    
                case SDLK_UP:
                    direction -= 3;
                    break;
                    
                case SDLK_DOWN:
                    direction += 3;
                    break;

                case SDLK_LEFT:
                    direction -= 1;
                    break;

                case SDLK_RIGHT:
                    direction += 1;
                    break;
                    
                case SDLK_1:
                    model -> char_attack( 0 );
                    break;
                    
                case SDLK_2:
                    model -> char_attack( 1 );
                    break;

                default:
                    break;
    
        }
    }
    
    model -> move_character(direction);
}

void imp_controller::key_pressed(SDL_Keysym key) {
    
    key_state.insert(key.sym);
}

void imp_controller::key_unpressed(SDL_Keysym key) {
    
    key_state.erase(key.sym);
}

