//
//  object.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "object.hpp"

object::object( void ) {
    
    crnt_pos.set_x(640);
    crnt_pos.set_y(840);
    
    are.set_h(0);
    are.set_w(0);
}

object::object(const position & position) {
    
    crnt_pos.set_x(position.get_x());
    crnt_pos.set_y(position.get_y());
}

object::object(const position & position, const area & area) {
    
    crnt_pos.set_x(position.get_x());
    crnt_pos.set_y(position.get_y());
    
    are.set_h(area.get_h());
    are.set_w(area.get_w());
}

bool object::intersects(object * other) {
    
    position othr_pos = other -> get_position();
    area     othe_are = other -> get_area();
    
    position tl1 = crnt_pos;
    position dr1 = position( crnt_pos.get_x() + are.get_w(), crnt_pos.get_y() + are.get_h() );
    position tl2 = othr_pos;
    position dr2 = position( othr_pos.get_x() + othe_are.get_w(), othr_pos.get_y() + othe_are.get_h()  );
    
    return overlap( tl1, dr1, tl2, dr2 );
}

bool object::overlap( position & top_left_1, position & down_rigt_1, position & top_left_2, position & down_rigt_2 ) {
         
    // If one rectangle is on left side of other
    if ( top_left_1.get_x() > down_rigt_2.get_x() || top_left_2.get_x() > down_rigt_1.get_x() )   {
        
        return false;
    }
    // If one rectangle is above other
    if ( down_rigt_1.get_y() < top_left_2.get_y() || down_rigt_2.get_y() < top_left_1.get_y() )    {
        
        return false;
    }
    return true;
}

void object::set_position( const position & pos ) {
    
    crnt_pos.set_x( pos.get_x() );
    crnt_pos.set_y( pos.get_y() );
}

position & object::get_position( void ) {
    
    return crnt_pos;
}
    
area & object::get_area( void ) {
    
    return are;
}
