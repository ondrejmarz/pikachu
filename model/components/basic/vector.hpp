//
//  vector.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef vector_hpp
#define vector_hpp

class vector {
    
public:
    
                    vector          ( void )                : x(0), y(0) { }
                    vector          ( double x, double y )  : x(x), y(y) { }
    
    double          get_x           ( void )                { return x; }
    double          get_y           ( void )                { return y; }
    
    void            set_x           ( double x )            { this -> x = x; }
    void            set_y           ( double y )            { this -> y = y; }
    
private:
    
    double x;
    double y;
};

#endif /* vector_hpp */
