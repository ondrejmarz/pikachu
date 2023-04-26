//
//  game_model.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "../config.h"
#include "game_model.hpp"
#include "../command/i_command.hpp"
#include "components/character/impl_character.hpp"

game_model::game_model(): main_char(&pikachu) {
    
    // WINDOW
    map_limiters.push_back(new object( position( 0, -WALL_THICKNESS ), area( SCREEN_WIDTH,  WALL_THICKNESS  ) ));
    map_limiters.push_back(new object( position( -WALL_THICKNESS, 0 ), area( WALL_THICKNESS, SCREEN_HEIGHT  ) ));
    map_limiters.push_back(new object( position( 0,   SCREEN_HEIGHT ), area( SCREEN_WIDTH, WALL_THICKNESS   ) ));
    map_limiters.push_back(new object( position( SCREEN_WIDTH, 0    ), area( WALL_THICKNESS,  SCREEN_HEIGHT ) ));
    
    float RESIZE_X = (float)SCREEN_WIDTH  / (float)BCKG_WIDTH;
    float RESIZE_Y = (float)SCREEN_HEIGHT / (float)BCKG_HEIGHT;
    
    // BCKG
    map_limiters.push_back(new object( position( 0, 105 * RESIZE_Y ),     area( 112 * RESIZE_X, 1 ) ));
    map_limiters.push_back(new object( position( SCREEN_WIDTH - (97 * RESIZE_X), 105 * RESIZE_Y ), area( 113 * RESIZE_X, 0 ) ));
}

int game_model::char_pos_x() { return (int) main_char -> get_position().get_x(); }
int game_model::char_pos_y() { return (int) main_char -> get_position().get_y(); }

int game_model::char_moves_size() { return main_char -> get_moves_num(); }

int game_model::char_state() { return main_char -> get_facing(); }

int game_model::char_move_in_use() { return main_char -> get_move_in_use(); }

void game_model::add_command( i_command * command ) {
    
    queue_commands.push( command );
}

void game_model::exe_commands( void ) {
    
    while (!queue_commands.empty()) {
     
        queue_commands.front() -> execute();
        queue_commands.pop();
    }
}

// objekt by měl býz zodpovědný jak si hejbe s

void game_model::update( void ) {
    
    exe_commands();
    
    if (main_char -> can_move()) {
        main_char -> step();
    }
}

bool game_model::check_char_collisions( void ) {
    
    for (auto const &i: map_limiters) {
     
        if (main_char -> intersects(i)) return true;
    }
    return false;
}

bool game_model::char_standing_still( void ) {
    
    return false;
}

void game_model::char_attack(int num) {
    
    if (! main_char -> can_move()) return;
    
    int move_id = main_char -> use_attack(num);
    
    //SDL_Rect move_size = all_moves.at( main_char -> use_attack(num)).getAOE();
    
    //todo
}

// -4   -3   -2
//
// -1    0    1
//
//  2    3    4

void game_model::move_character(int dir) {
    
    main_char -> set_direction(dir);
}
