//
//  characters.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef characters_hpp
#define characters_hpp

#include "../interfaces/i_character.hpp"

class angry: public i_character {
    
public:
    angry( int pos_x, int pos_y );
    
    int use_attack (int num);
    
    bool is_attacking       ( void );
    bool can_move           ( void );
    
private:
    timer   stunned;
};



class character: public i_character  {
    
public:
    
    character(enum_typing type, int atck, int dfns, int stmn/*, int basc_spd, int atck_spd, int dfns_spd*/, const position & pos, const area & ar);
    
    int     use_attack              (int num) override;
    
    bool    is_attacking            ( void ) override;
    bool    is_still                ( void );
    bool    can_move                ( void ) override;
    
    //void    accept                  ( visitor * ) const;
    
private:
    timer   standing_still;
};

character::character(enum_typing type, int atck, int dfns, int stmn/*, int basc_spd, int atck_spd, int dfns_spd*/, const position & pos, const area & ar)

: i_character( pos, ar,
               type,
               atck,
               dfns,
               stmn/*,
               basc_spd,
               atck_spd,
               dfns_spd */), standing_still(5)
{ }

int character::use_attack(int num) {
    
    if (num >= moves_id.size()) return -1;
    
    charging_attack.reset();
    move_in_use = moves_id.at(num);
    
    return move_in_use;
}

bool character::is_attacking( void ) {
    
    // attack just finished
    if (charging_attack.elapsed(1.2) && move_in_use != -1 ) {
        
        standing_still.reset();
        move_in_use = -1;
        return false;
    }
    // attack not happening
    if (move_in_use == -1) {
    
        return false;
    }
    
    // is attacking
    return true;
}

bool character::is_still( void ) {
    
    return standing_still.elapsed(5);
}

bool character::can_move( void ) {
    
    if (!is_attacking()) {
        
        if (want_move()) standing_still.reset();
        
        return true;
    }
    return false;
}

static character pikachu(electric, 100, 120, 100,/* 20, 20, 20,*/ position(640, 60), area(26, 28) );


#endif /* characters_hpp */
