//
//  position.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef position_hpp
#define position_hpp

#include "vector.hpp"

class position {
    
public:
                    position            ( void )                : x(0), y(0) { }
                    position            ( double x, double y )  : x(x), y(y) { }
    
    double          get_x               ( void ) const          { return x; }
    double          get_y               ( void ) const          { return y; }
    
    void            set_x               ( double x )            { this -> x = x; }
    void            set_y               ( double y )            { this -> y = y; }
    
    void add_x ( double value ) {
        
        x += value;
    }
    
    void add_y ( double value ) {
        
        y += value;
    }
    
    void add (vector v) {
        
        set_x( get_x() + v.get_x() );
        set_y( get_y() + v.get_y() );
    }
    
private:
    double x;
    double y;
};

#endif /* position_hpp */
