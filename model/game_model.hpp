//
//  game_model.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef game_model_hpp
#define game_model_hpp

#include "characters.hpp"

class i_command;

#include <queue>
#include <vector>

class game_model {
    
public:
    
                        game_model          ( void );
    
    /**
     * Method to add command for executions
     *
     * \param command to be executed
     *
     * \since This function is available since 1.0
     *
     * \sa exe\_commands()
     *
     */
    void                add_command         ( i_command * command);
    void                exe_commands        ( void );
    
    void                update              ( void );
    
    /**
     * Character oriented methods
     */
    void    char_stop               ( void );
    int     char_pos_x              ( void );
    int     char_pos_y              ( void );
    int     char_moves_size         ( void );
    int     char_state              ( void );
    int     char_move_in_use        ( void );
    bool    char_standing_still     ( void );
    bool    is_char_attacking       ( void );
    void    char_attack             (int num);
    
    void    move_character          (int direction);
    
    void    check_char_collisions   ( void );
    
    void    move_expiration         ( void );
    void    moves_hit_angry         ( void );
    void    delete_dead             ( void );
    
    bool    check_char_coll_upst    ( void );
    bool    check_char_coll_down    ( void );
    bool    check_char_coll_left    ( void );
    bool    check_char_coll_rght    ( void );
    
    const std::vector < angry > & get_enemies ( void );
    
private:
    
    std::queue  < i_command * > queue_commands = {};
    
    std::vector < wall > map_walls_rght;
    std::vector < wall > map_walls_left;
    std::vector < wall > map_walls_down;
    std::vector < wall > map_walls_upst;
    
    std::vector < angry > enemies;
    std::vector < move  > attacks;
    
    pikachu pika;
};

#endif /* game_model_hpp */
