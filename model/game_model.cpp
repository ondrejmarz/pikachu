//
//  game_model.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "game_model.hpp"
#include "../command/i_command.hpp"

static const pikachu p(electric, 100, 120, 100, position(640, 60), area(26, 28));

game_model::game_model(): pika( p ) {
    
    // ENEMY INIT
    enemies.emplace_back( angry(200, 300) );
    enemies.emplace_back( angry(100, 400) );
    enemies.emplace_back( angry(300, 350) );
    
    // WINDOW
    //upst
    map_walls_upst.emplace_back(wall( position(0, 10),       area(SCREEN_W, 15) ));
    map_walls_down.emplace_back(wall( position(0, SCREEN_H), area(SCREEN_W, 5) ));
    //left
    map_walls_left.emplace_back(wall( position(-5, 0),       area(5, SCREEN_H) ));
    //right
    map_walls_rght.emplace_back(wall( position(SCREEN_W, 5), area(5, SCREEN_H) ));

    float RESIZE_X = (float)SCREEN_W / (float)BCKG_W;
    float RESIZE_Y = (float)SCREEN_H / (float)BCKG_H;
    
    // BCKG
    map_walls_down.emplace_back(wall( position(0,                          104 * RESIZE_Y ), area(112 * RESIZE_X, 4) ));
    map_walls_down.emplace_back(wall( position(SCREEN_W - (97 * RESIZE_X), 104 * RESIZE_Y ), area(97  * RESIZE_X, 4) ));
    
    // upst
    map_walls_upst.emplace_back(wall( position(0,                          112 * RESIZE_Y ), area(112 * RESIZE_X, 4) ));
    map_walls_upst.emplace_back(wall( position(SCREEN_W - (97 * RESIZE_X), 112 * RESIZE_Y ), area(97  * RESIZE_X, 4) ));
}

int game_model::char_pos_x() { return (int) pika.get_position().get_x(); }
int game_model::char_pos_y() { return (int) pika.get_position().get_y(); }

int game_model::char_moves_size() { return pika.get_moves_num(); }

int game_model::char_state() { if (char_standing_still()) return 4; return pika.get_facing(); }

int game_model::char_move_in_use() { return pika.get_move_in_use(); }

bool game_model::is_char_attacking() { return pika.is_attacking(); }

void game_model::add_command( i_command * command ) {
    
    queue_commands.push( command );
}

void game_model::exe_commands( void ) {
    
    while (!queue_commands.empty()) {
     
        queue_commands.front() -> execute();
        queue_commands.pop();
    }
}

void game_model::update( void ) {
    
    exe_commands();
    
    if (pika.can_move() && pika.want_move()) {
        
        check_char_collisions();
        pika.step();
    }
    
    move_expiration();
    moves_hit_angry();
    delete_dead();
}

bool common_intersects( const object & obj1, const object & obj2 ) {
    
    if ( obj1.get_other_side_y() < obj2.get_position().get_y() || obj2.get_other_side_y() < obj1.get_position().get_y() ) return false;
    if ( obj1.get_other_side_x() < obj2.get_position().get_x() || obj2.get_other_side_x() < obj1.get_position().get_x() ) return false;
    
    return true;
}

void game_model::moves_hit_angry( void ) {
    
    for (auto &e: enemies) {
        for (auto const &a: attacks) {
            
            if (common_intersects(e, a))
                e.recive_damage( pika.get_atck(), pika.has_atck_stab(a), a );
        }
    }
}

void game_model::delete_dead( void ) {
    
    std::erase_if( enemies, [](const angry &e) { return e.is_dead();    } );
}

void game_model::move_expiration( void ) {
    
    std::erase_if( attacks, [](const move  &m) { return m.did_expire(); } );
}

void game_model::check_char_collisions( void ) {
    
    int allwd_dir = 0;
    int wantd_dir = pika.get_direction() + 4;
    
    if ( wantd_dir % 3 == 0 && check_char_coll_left() ) // definitely going left
        allwd_dir += -1;
    else if ( (wantd_dir - 2) % 3 == 0 && check_char_coll_rght() ) // definitely going right
        allwd_dir += 1;
    
    if ( wantd_dir < 3 && check_char_coll_upst() ) // definitely going up
        allwd_dir += -3;
    else if ( wantd_dir > 5 && check_char_coll_down() ) // definitely going down
        allwd_dir += 3;
    
    move_character(allwd_dir);
}

bool game_model::char_standing_still( void ) {
    
    return pika.is_still();
}

void game_model::char_attack(int num) {
    
    if (pika.can_move()) {
        pika.use_attack(num);
        attacks.push_back( move( electric, 100, 100, position(pika.get_position().get_x()-50,pika.get_position().get_y()-50), area(100, 100) ) );
    }
}

// -4   -3   -2
//
// -1    0    1
//
//  2    3    4

void game_model::move_character(int dir) {
    
    pika.set_direction(dir);
}

bool intersects( const object & character, const object & obj ) {
    
    // one is above the other
    // check only feet position
    if ( character.get_other_side_y() < obj.get_position().get_y() || obj.get_other_side_y() < character.get_other_side_y() ) return false;
    
    // one is on the left of the other
    if ( character.get_other_side_x() < obj.get_position().get_x() || obj.get_other_side_x() < character.get_position().get_x() ) return false;
    
    return true;
}

// potřebuju kontrolovat jen pozici nohou u postavy
bool game_model::check_char_coll_left( void ) {
    for (auto const &i: map_walls_left) if (intersects(pika, i)) return false;
    return true;
}

bool game_model::check_char_coll_rght( void ) {
    for (auto const &i: map_walls_rght) if (intersects(pika, i)) return false;
    return true;
}

bool game_model::check_char_coll_upst( void ) {
    for (auto const &i: map_walls_upst) if (intersects(pika, i)) return false;
    return true;
}

bool game_model::check_char_coll_down( void ) {
    for (auto const &i: map_walls_down) if (intersects(pika, i)) return false;
    return true;
}

const std::vector < angry > & game_model::get_enemies( void ) {
    return enemies;
}
