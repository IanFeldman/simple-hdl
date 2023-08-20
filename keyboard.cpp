#include <SDL2/SDL.h>
#include <stdio.h>
#include "keyboard.hpp"

#include <iostream>

Keyboard::Keyboard()
    :Module("KEYBOARD", "built-in")
{
}

const std::unordered_set<std::string> Keyboard::valid_keys = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
};

void Keyboard::evaluate() {
    std::cout<< "eval keyboard" << std::endl;

    // clear outputs
    for (auto& it: m_outputs) {
        m_outputs[it.first] = 0;
    }
    std::cout<< "inputs cleared" << std::endl;

    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);
    // iterate over outputs
    for (auto& it : m_outputs) {
        // TODO: map output to SDL_SCANCODE
        if (it.first == "A") {
            m_outputs["A"] = keyboard_state[SDL_SCANCODE_A];
        }
    }

    // poll for keyboard events
    /*
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_KEYDOWN:
                std::cout<< "keydown" << std::endl;
                m_outputs[SDL_GetKeyName(event.key.keysym.sym)] = 1;
                break;
            default:
                break;
        }
    }
    */
}
