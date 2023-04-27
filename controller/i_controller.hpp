//
//  i_controller.hpp
//  pikachu
//
//  Created by Ondřej März on 26.04.2023.
//

#ifndef i_controller_hpp
#define i_controller_hpp

class game_model;

#include <SDL2/SDL.h>

/**
 * Abstract controller class.
 *
 * Provides common interface for all controllers.
 * In future needs to get rid of SDL library dependency.
 *
 * \since This function is available since 1.0.
 *
 */
class i_controller {
    
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
    i_controller(game_model * model): model(model) { }
    
    /**
     * Reacts on user input.
     *
     * Applies changes to  game model methods.
     *
     * \since This function is available since 1.0.
     *
     */
    virtual void handle_input() = 0;
    
    /**
     * Registers pressed key.
     *
     * Adds pressed key to set of pressed keys.
     *
     * \since This function is available since 1.0.
     *
     */
    virtual void key_pressed(SDL_Keysym key) = 0;
    
    /**
     * Registers released key.
     *
     * Erases pressed key from set of pressed keys.
     *
     * \since This function is available since 1.0.
     *
     */
    virtual void key_released(SDL_Keysym key) = 0;
    
protected:
    
    /**
     * Set of pressed keys.
     *
     * Stores keys that are pressed.
     * Input handling method iterates this sit.
     *
     * \since This variable is available since 1.0.
     *
     */
    std::set<SDL_Keycode> key_state;
    
    /**
     * Pointer to game model.
     *
     * Pointer to game model where are changes applied to.
     *
     * \since This variable is available since 1.0.
     *
     */
    game_model * model;
};

#endif /* i_controller_hpp */
