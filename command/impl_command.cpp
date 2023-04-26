//
//  impl_command.cpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#include "impl_command.hpp"
#include "../model/game_model.hpp"

// -4   -3   -2
//
// -1    0    1
//
//  2    3    4

void move_char_up_command::execute() const {
    model -> move_character(-3);
}

void move_char_down_command::execute() const {
    model -> move_character(3);
}

void move_char_left_command::execute() const {
    model -> move_character(-1);
}

void move_char_right_command::execute() const {
    model -> move_character(1);
}
