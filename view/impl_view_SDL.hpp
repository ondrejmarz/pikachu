//
//  impl_view_SDL.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef impl_view_SDL_hpp
#define impl_view_SDL_hpp

class game_model;

#include "i_view.hpp"

#include <SDL2/SDL.h>
#include <iostream>

class imp_view_SDL: public i_view {
    
public:
    imp_view_SDL( game_model * model );
    ~imp_view_SDL();
    
    bool init() override;
    void update() override;
    
    void draw_bckg();
    void draw_ui();
    void draw_char();
    
    void draw_char_move (int move_id);
    void draw_char_run();
    
private:
    
    SDL_Texture * load_texture( std::string path );
    
    game_model * model;
    
    
    SDL_Rect char_text_states[ 30 ];
    SDL_Rect move_texture_animation[6];
    
    SDL_Window      * window;
    
    SDL_Renderer * renderer;

    SDL_Texture * bckg_texture;
    SDL_Texture * char_texture;
    SDL_Texture * move_texture;
    
    // UI
    SDL_Texture *                   frame_texture;
    SDL_Texture *                   ends_frame_texture;
    std::vector<SDL_Texture *>      moves_texture;
};

#endif /* impl_view_SDL_hpp */
