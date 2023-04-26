//
//  main.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "model/game_model.hpp"
#include "view/impl_view_SDL.hpp"
#include "controller/impl_controller.hpp"

int main (int argc, const char **argv) {
    
    //const int SCREEN_FPS = 60;
    //const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    
    i_view * game_view;
    i_controller * game_control;
    game_model * game_model;
    
    game_model = new class game_model();
    game_view = new imp_view_SDL( game_model );
    game_control = new imp_controller( game_model );
    
    if (! game_view -> init() ) return 1;
    
    auto start = SDL_GetTicks();
    auto end   = SDL_GetTicks();
    
    SDL_Event e;
    bool quit = false;
    
    while ( !quit ) {
        
        if (end-start < 1000/60.0)
            SDL_Delay((1000/60.0) - (end-start));
        
        start = SDL_GetTicks();
        
        while ( SDL_PollEvent( &e ) ) {
            
            if      ( e.type == SDL_QUIT    ) quit = true;
            else if ( e.type == SDL_KEYDOWN ) game_control -> key_pressed(e.key.keysym);
            else if ( e.type == SDL_KEYUP   ) game_control -> key_unpressed(e.key.keysym);
        }
        
        game_control    -> handle_input();
        game_model      -> update();
        game_view       -> update();
        
        end = SDL_GetTicks();
    }
    
    free(game_control);
    free(game_view);
    free(game_model);
    
    return 0;
}
