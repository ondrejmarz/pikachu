//
//  i_command.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_command_hpp
#define i_command_hpp

class game_model;

class i_command {
    
public:
    
    i_command( game_model * model ): model(model) { }
    
    virtual void execute() const = 0;
    
protected:
    
    game_model * model;
};

#endif /* i_command_hpp */
