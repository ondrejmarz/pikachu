//
//  impl_controller.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef impl_controller_hpp
#define impl_controller_hpp

#include<set>

#include "i_controller.hpp"

/**
 * Interface for controller class.
 *
 * Reacts on user input and does changes to game model.
 *
 * \since This class is available since 1.0
 *
 */
class impl_controller: public i_controller {
    
public:
    /**
     * Controller constructor
     *
     * Constructs controller
     *
     * \param model that changes will be applied to
     *
     * \since This function is available since 1.0
     *
     */
    impl_controller(game_model * model): i_controller(model) { }
    
    /**
     * Reacts on user input.
     *
     * Iterates over pressed keys and calls game model methods.
     *
     * \since This function is available since 1.0.
     *
     */
    void handle_input( void );
    
    /**
     * Registers pressed key.
     *
     * Adds pressed key to set of pressed keys.
     *
     * \since This function is available since 1.0.
     *
     */
    void key_pressed(SDL_Keysym key);
    
    /**
     * Registers released key.
     *
     * Erases pressed key from set of pressed keys.
     *
     * \since This function is available since 1.0.
     *
     */
    void key_released(SDL_Keysym key);
    
};

#endif /* impl_controller_hpp */
