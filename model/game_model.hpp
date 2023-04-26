//
//  game_model.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef game_model_hpp
#define game_model_hpp

class i_command;
class i_character;
class object;

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
    void    char_attack             (int num);
    
    void    move_character          (int direction);
    
    bool    check_char_collisions   ( void );
    
private:
    
    std::queue  < i_command * > queue_commands = {};
    std::vector < object    * > map_limiters = {};
    
    i_character * main_char = NULL;
};

#endif /* game_model_hpp */
