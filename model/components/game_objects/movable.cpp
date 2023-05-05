//
//  i_movable.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "objects.hpp"

i_movable::i_movable( void ): object(), direction(0), last_step(0) { }

i_movable::i_movable( const position & pos, const area & ar ): object(pos, ar), direction(0), last_step(0) { }

i_movable::i_movable( const position & pos, const area & ar, int dir ): object(pos, ar), direction(dir), last_step(0) { }


void i_movable::step( void ) {
    
    if (direction == 0) return;
    
    last_step = direction;
    
    switch (direction+4) {
        case 0:
            crnt_pos.add_x(-DGNL_STEP);
            crnt_pos.add_y(-DGNL_STEP);
            break;
            
        case 1:
            crnt_pos.add_y(-NRML_STEP);
            break;
            
        case 2:
            crnt_pos.add_x(DGNL_STEP);
            crnt_pos.add_y(-DGNL_STEP);
            break;
            
        case 3:
            crnt_pos.add_x(-NRML_STEP);
            break;
            
        case 5:
            crnt_pos.add_x(NRML_STEP);
            break;
            
        case 6:
            crnt_pos.add_x(-DGNL_STEP);
            crnt_pos.add_y(DGNL_STEP);
            break;
            
        case 7:
            crnt_pos.add_y(NRML_STEP);
            break;
            
        case 8:
            crnt_pos.add_x(DGNL_STEP);
            crnt_pos.add_y(DGNL_STEP);
            break;
            
        default:
            break;
    }
}

bool i_movable::want_move ( void ) {
    
    return direction != 0;
}

void i_movable::set_direction(int dir) {
    
    direction = dir;
}

// -4   -3   -2
//
// -1    0    1
//
//  2    3    4

int i_movable::get_direction() {
    
    return direction;
}

//  0    1    2
//
//  3    4    5
//
//  6    7    8

int i_movable::get_facing() {
    
    return last_step + 4;
}
