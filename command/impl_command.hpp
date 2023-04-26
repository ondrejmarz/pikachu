//
//  impl_command.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef impl_command_hpp
#define impl_command_hpp

#include "i_command.hpp"

class move_char_up_command: public i_command {
    
public:
    move_char_up_command(game_model * model): i_command(model) { }
    
    void execute() const override;
};

class move_char_down_command: public i_command {
    
public:
    move_char_down_command(game_model * model): i_command(model) { }
    
    void execute() const override;
};

class move_char_right_command: public i_command {
    
public:
    move_char_right_command(game_model * model): i_command(model) { }
    
    void execute() const override;
};

class move_char_left_command: public i_command {
    
public:
    move_char_left_command(game_model * model): i_command(model) { }
    
    void execute() const override;
};

#endif /* impl_command_hpp */
