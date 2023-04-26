//
//  object.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef object_hpp
#define object_hpp

#include <iostream>

#include "position.hpp"
#include "area.hpp"

enum typing { bug, dark, dragon, electric, fairy, fighting, fire, flying, ghost, ground, grass, ice, normal, poison, psychic, rock, steel, water };

class object {
    
public:
    object();
    object(const position &);
    object(const position &, const area &);
    
    position & get_position( void );
    area     & get_area    ( void );
    
    void set_position( const position & pos );
    
    bool intersects( object * other );
    
    //virtual void accept( visitor * ) const = 0;
    
protected:
    position crnt_pos;
    area     are;
    
    bool overlap(position &, position &, position &, position &);
};

#endif /* object_hpp */
