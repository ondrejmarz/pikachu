//
//  angry.cpp
//  pikachu
//
//  Created by Ondřej März on 28.04.2023.
//

#include "i_character.hpp"
#include "typing.hpp"
#include "characters.hpp"

angry::angry( int pos_x, int pos_y ): i_character( position(pos_x, pos_y), area(20, 20), bug, 20, 20, 20 ) { }

int angry::use_attack (int num) {
    
    return -1;
}

bool angry::is_attacking       ( void ) {
    
    return false;
}

bool angry::can_move           ( void ) {
    
    return stunned.elapsed( 1.6 );
}

