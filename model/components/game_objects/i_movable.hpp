//
//  i_movable.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_movable_hpp
#define i_movable_hpp

#include "object.hpp"

class i_movable: public object {
    
public:
    
      i_movable     ( void );
      i_movable     ( const position & pos, const area & ar );
      i_movable     ( const position & pos, const area & ar, int dir );
    
    virtual void step(   void   );
    virtual void set_direction( int dir );
    virtual bool want_move();
    
    virtual int  get_direction( );
    virtual int  get_facing();
    
protected:
    
    int direction;
    int last_step;
    
    void step_x(int);
    void step_y(int);
    
    bool is_at_target_x();
    bool is_at_target_y();
};

class move: public object {
    
public:
    move( typing type, int power, int accuracy, position pos, area area_of_effect)
    : object(pos, area_of_effect), type(type), power(power), accur(accuracy) {}
    
private:
    typing type;
    
    int power;
    int accur;
};

static move discharge( electric, 100, 100, position(-50, -50), area(100, 100) );
static move iron_tail( steel, 150, 80, position(-25, 0), area(50, 70) );

#endif /* i_movable_hpp */
