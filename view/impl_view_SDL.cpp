//
//  impl_view_SDL.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "impl_view_SDL.hpp"
#include "../model/game_model.hpp"
#include "../config.h"

#include <SDL2_image/SDL_image.h>

SDL_Surface * load_surface( std::string path )
{
    //Load image at specified path
    SDL_Surface * loaded_surface = SDL_LoadBMP( path.c_str() );
    
    if ( loaded_surface == NULL ) std::cout << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;

    return loaded_surface;
}

SDL_Rect * create_rect( int x, int y, int w, int h ) {
    
    SDL_Rect * rect = new SDL_Rect{x, y, w, h};
    
    return rect;
}

SDL_Texture * imp_view_SDL::load_texture( std::string path )
{
    //The final texture
    SDL_Texture * new_texture = NULL;

    //Load image at specified path
    SDL_Surface * loaded_surface = IMG_Load( path.c_str() );
    
    if ( loaded_surface == NULL ) return NULL;
    
    //Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface( renderer, loaded_surface );
       
    //Get rid of old loaded surface
    SDL_FreeSurface( loaded_surface );

    return new_texture;
}

imp_view_SDL::imp_view_SDL( game_model * model )
: model(model), window(NULL), bckg_texture(NULL), renderer(NULL), frame_texture(NULL), ends_frame_texture(NULL),
  char_texture(NULL), move_texture(NULL)
{ }

imp_view_SDL::~imp_view_SDL() {
    
    SDL_DestroyTexture( frame_texture );
    SDL_DestroyTexture( ends_frame_texture );
    SDL_DestroyTexture( bckg_texture );
    SDL_DestroyTexture( char_texture );
    SDL_DestroyTexture( move_texture );
    
    SDL_DestroyRenderer(renderer);
    
    SDL_DestroyWindow( window );
    
    IMG_Quit();
    SDL_Quit();
}

bool imp_view_SDL::init ( void ) {
    
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow( "Pokémon: WILD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if (window == NULL) {
        
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    
    if ( renderer == NULL ) {
        
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
        
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    
    bckg_texture = load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/arena.png");
    
    if ( bckg_texture == NULL ) {
        
        return false;
    }
    
    SDL_RenderCopy(renderer, bckg_texture, NULL, NULL );
    
    char_texture = load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/pikachu.png");
    move_texture = load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/moves/discharge.png");
    
    frame_texture = load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/ui/frame.png");
    ends_frame_texture = load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/ui/end_frame.png");
    
    
    //  6    7    0
    //
    //  5    8    1
    //
    //  4    3    2
    
    // -4   -3   -2
    //
    // -1    0    1
    //
    //  2    3    4
    
    //  0    1    2
    //
    //  3    4    5
    //
    //  6    7    8
    
    // TR
    char_text_states[2].x = 312;
    char_text_states[2].y = 30;
    char_text_states[2].h = 27;
    char_text_states[2].w = 26;
    
    // R
    char_text_states[5].x = 297;
    char_text_states[5].y = 118;
    char_text_states[5].h = 27;
    char_text_states[5].w = 27;
    
    // DR
    char_text_states[8].x = 329;
    char_text_states[8].y = 176;
    char_text_states[8].h = 27;
    char_text_states[8].w = 27;
    
    // D
    char_text_states[7].x = 28;
    char_text_states[7].y = 235;
    char_text_states[7].h = 27;
    char_text_states[7].w = 24;
    
    // DL
    char_text_states[6].x = 37;
    char_text_states[6].y = 176;
    char_text_states[6].h = 27;
    char_text_states[6].w = 27;
    
    // L
    char_text_states[3].x = 11;
    char_text_states[3].y = 91;
    char_text_states[3].h = 27;
    char_text_states[3].w = 27;
    
    // TL
    char_text_states[0].x = 53;
    char_text_states[0].y = 30;
    char_text_states[0].h = 27;
    char_text_states[0].w = 26;
    
    // T
    char_text_states[1].x = 96;
    char_text_states[1].y = 4;
    char_text_states[1].h = 26;
    char_text_states[1].w = 24;
    
    char_text_states[4].x = 244;
    char_text_states[4].y = 234;
    char_text_states[4].h = 27;
    char_text_states[4].w = 24;
    
    //DISCHARGE
    char_text_states[20].x =196;
    char_text_states[20].y =237;
    char_text_states[20].h =27;
    char_text_states[20].w =25;
    
    char_text_states[21].x =133;
    char_text_states[21].y =236;
    char_text_states[21].h =27;
    char_text_states[21].w =24;
    
    char_text_states[22].x =155;
    char_text_states[22].y =234;
    char_text_states[22].h =27;
    char_text_states[22].w =21;
    
    char_text_states[23].x =173;
    char_text_states[23].y =234;
    char_text_states[23].h =27;
    char_text_states[23].w =21;
    
    char_text_states[24].x =173;
    char_text_states[24].y =234;
    char_text_states[24].h =27;
    char_text_states[24].w =21;
    
    char_text_states[25].x =173;
    char_text_states[25].y =234;
    char_text_states[25].h =27;
    char_text_states[25].w =21;
    
    // MOVE ANIMATION
    move_texture_animation[0].x = 0;
    move_texture_animation[0].y = 0;
    move_texture_animation[0].w = 1;
    move_texture_animation[0].h = 1;
    
    move_texture_animation[1].x = 0;
    move_texture_animation[1].y = 0;
    move_texture_animation[1].w = 1;
    move_texture_animation[1].h = 1;
    
    move_texture_animation[2].x = 0;
    move_texture_animation[2].y = 0;
    move_texture_animation[2].w = 128;
    move_texture_animation[2].h = 128;
    
    move_texture_animation[3].x = 128;
    move_texture_animation[3].y = 0;
    move_texture_animation[3].w = 128;
    move_texture_animation[3].h = 128;
    
    move_texture_animation[4].x = 256;
    move_texture_animation[4].y = 0;
    move_texture_animation[4].w = 128;
    move_texture_animation[4].h = 128;
    
    move_texture_animation[5].x = 384;
    move_texture_animation[5].y = 0;
    move_texture_animation[5].w = 128;
    move_texture_animation[5].h = 128;
    /*
    int i = 0;
    
    while (i < model -> char_moves_size()) {
        
        moves_surface.push_back(load_surface("/Users/ondrejmars/Desktop/pro_grams/game/assets/moves/" + model ->char_move_name(i) + ".bmp"));
        i++;
    }*/
    
    moves_texture.push_back(load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/moves/iron_tail_icon.png"));
    moves_texture.push_back(load_texture("/Users/ondrejmars/Desktop/pro_grams/game/assets/moves/discharge_icon.png"));
    
    SDL_RenderPresent( renderer );
    
    return true;
}

void imp_view_SDL::update ( void ) {
    
    SDL_RenderClear( renderer );
    
    draw_bckg();
    draw_char();
    draw_ui();
    
    SDL_RenderPresent( renderer );
}

void imp_view_SDL::draw_bckg() {
    
    SDL_RenderCopy(renderer, bckg_texture, NULL, NULL );
}

void imp_view_SDL::draw_char() {
    
    // When is spell casting
    if (model -> char_move_in_use() != -1) {
        
        draw_char_move(model -> char_move_in_use());
        update_cnt++;
    }
    // Otherwise
    else {
        
        if (update_cnt >= 40) { update_cnt = 10; draw_char_move(1); }
        else if (update_cnt > 0) { update_cnt--; draw_char_move(1); }
        else {
            draw_char_run();
            update_cnt = 0;
        }
    }
}

void imp_view_SDL::draw_char_move(int move_id) {
    
    if (update_cnt > 59) update_cnt = 40;
    
    SDL_RenderCopy(renderer,
                   move_texture,
                   &move_texture_animation[ (int)(update_cnt/10) ],
                   create_rect(
                        model->char_pos_x() - 54,
                        model->char_pos_y() - 48,
                        move_texture_animation[ (int)(update_cnt/10) ].w,
                        move_texture_animation[ (int)(update_cnt/10) ].h ) );
    
    SDL_RenderCopy(renderer,
                   char_texture,
                   &char_text_states[ 20 + (int)(update_cnt/10) ],
                   create_rect(
                        model->char_pos_x(),
                        model->char_pos_y(),
                        char_text_states[ 20 + (int)(update_cnt/10) ].w,
                        char_text_states[ 20 + (int)(update_cnt/10) ].h ) );
}


void imp_view_SDL::draw_char_run (void) {
    
    SDL_Rect * src_rec = &char_text_states[ model->char_state() ];
    
    SDL_RenderCopy(renderer,
                   char_texture,
                   src_rec,
                   create_rect(
                        model->char_pos_x(),
                        model->char_pos_y(),
                        src_rec->w,
                        src_rec->h ) );
}

void imp_view_SDL::draw_ui() {
    
    {
        int UI_HEIGHT = 20;
        
        // LEFT SIDE OF FRAME
        SDL_RenderCopy(renderer, ends_frame_texture, create_rect(16, 0, 16, 32), create_rect(10, UI_HEIGHT, 32, 64));
        
        int i = 0;
        
        while (i < model -> char_moves_size()) {
            
            // FRAME AND MOVE IN IT
            SDL_RenderCopy(renderer, frame_texture,         NULL, create_rect(42 +      (i * 64), UI_HEIGHT,    64, 64));
            SDL_RenderCopy(renderer, moves_texture.at(i),   NULL, create_rect(42 + 10 + (i * 64), UI_HEIGHT+10, 44, 44));
            
            i++;
        }
        
        // RIGHT SIDE OF FRAME
        SDL_RenderCopy(renderer, ends_frame_texture, create_rect(0, 0, 16, 32), create_rect(42 + (i * 64), UI_HEIGHT, 32, 64));
    }
}
