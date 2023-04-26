//
//  impl_character.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef impl_character_hpp
#define impl_character_hpp

#include "../character/i_character.hpp"

class character: public i_character  {
    
public:
    
    character(typing type, std::string name, int atck, int dfns, int stmn, int basc_spd, int atck_spd, int dfns_spd, std::vector<move> moves, const position & pos, const area & ar);
    
    int     use_attack              (int num) override;
    
    bool    can_move                (void) override;
    
    //void    accept                  ( visitor * ) const;
};

character::character(typing type, std::string name, int atck, int dfns, int stmn, int basc_spd, int atck_spd, int dfns_spd, std::vector<move> moves, const position & pos, const area & ar)

: i_character( pos, ar,
               type,
               name,
               atck,
               dfns,
               stmn,
               basc_spd,
               atck_spd,
               dfns_spd,
               moves)
{ }

int character::use_attack(int num) {
    
    if (num >= moves_id.size()) return -1;
    
    charging_attack.reset();
    move_in_use = moves_id.at(num);
    
    return move_in_use;
}

bool character::can_move( void ) {
    
    if (move_in_use == -1)
        return true;
    else if (charging_attack.elapsed(1)) {
        move_in_use = -1;
        return true;
    }
    
    return false;
}

/*
void character::deal_damage_to( character * other ) {
    
    
}*/

static character pikachu(electric, "Pikachu", 100, 120, 100, 20, 20, 20, {discharge, iron_tail}, position(640, 60), area(26, 28) );


#endif /* impl_character_hpp */
