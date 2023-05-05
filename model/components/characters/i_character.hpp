//
//  i_character.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_character_hpp
#define i_character_hpp

#include "../basic/typing.hpp"
#include "../basic/timer.hpp"
#include "../interfaces/i_movable.hpp"

#include <vector>

class i_character: public i_movable  {
    
public:
    i_character(const position & pos, const area & ar, enum_typing type, int atck, int dfns, int stmn/*, int basc_spd, int atck_spd, int dfns_spd */)
    
    :   i_movable(pos, ar),
        type(type),
        atck(atck),
        dfns(dfns),
        stmn(stmn),
        //basc_spd(basc_spd),
        //atck_spd(atck_spd),
        //dfns_spd(dfns_spd),
        moves_id({0, 1}),
        move_in_use(-1)
    { }
    
    virtual int use_attack (int num) = 0;
    virtual int get_moves_num (void) const { return (int) moves_id.size(); }
    virtual int get_move_in_use(void) const { return move_in_use; }
    
    virtual bool is_dead( void ) const { return stmn > 0; }
    virtual bool is_attacking( void ) = 0;
    virtual bool can_move( void ) = 0;
    
    bool has_atck_stab( const move & m ) {
        return typing::get_reference( m.get_typing() ).stab( type );
    }
    
    // move.accuracy is not used
    void recive_damage( int enemy_atck, bool stab_atck, const move & move_atck ) {
        
        float bonus = 1;
        
        // enemy has stab
        if (stab_atck) bonus += 0.2;
        
        // this is resistant to enemy attack
        if ( typing::get_reference( type ).is_resistant_to( move_atck.get_typing() ) ) bonus -= 0.2;
        
        // enemy is super or not very effective
        if ( typing::get_reference( move_atck.get_typing() ).super_effective( type ) ) bonus += 0.2 ;
        if ( typing::get_reference( move_atck.get_typing() ).not_very_effect( type ) ) bonus -= 0.2 ;
        
        stmn -= ( ((float)enemy_atck / (float)dfns) * (float)move_atck.get_power() * bonus );
    }
    
    int get_atck() { return atck; }
    int get_dfns() { return dfns; }
    int get_stmn() { return stmn; }
    
    //int get_atck_spd() { return atck_spd; }
    //int get_dfns_spd() { return dfns_spd; }
    //int get_basc_spd() { return basc_spd; }
    
protected:
    
    enum_typing type;
    
    int atck;
    int dfns;
    int stmn;
    
    //int atck_spd;
    //int dfns_spd;
    //int basc_spd;
    
    std::vector<int> moves_id;
    
    int move_in_use;
    
    timer charging_attack;
};

#endif /* i_character_hpp */
