//
//  impl_character.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "i_time_limited.hpp"
#include "../game_objects/i_movable.hpp"

#include <vector>

class i_character: public i_movable  {
    
public:
    i_character(const position & pos, const area & ar, typing type, std::string name, int atck, int dfns, int stmn, int basc_spd, int atck_spd, int dfns_spd, std::vector<move> moves)
    
    :   i_movable(pos, ar),
        type(type),
        name(name),
        atck(atck),
        dfns(dfns),
        stmn(stmn),
        basc_spd(basc_spd),
        atck_spd(atck_spd),
        dfns_spd(dfns_spd),
        moves_id({0, 1}),
        move_in_use(-1)
    { }
    
    virtual int use_attack (int num) = 0;
    virtual int get_moves_num (void) { return (int) moves_id.size(); }
    virtual int get_move_in_use(void) { return move_in_use; }
    virtual bool can_move(void) = 0;
    
protected:
    
    typing type;
    
    std::string name;
    
    int atck;
    int dfns;
    int stmn;
    
    int basc_spd;
    int atck_spd;
    int dfns_spd;
    
    std::vector<int> moves_id;
    
    int move_in_use;
    
    i_time_limited charging_attack;
};
