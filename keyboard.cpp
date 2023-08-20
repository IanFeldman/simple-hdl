#include <SDL2/SDL.h>
#include <stdio.h>
#include "keyboard.hpp"

#include <iostream>

Keyboard::Keyboard()
    :Module("KEYBOARD", "built-in")
{
}

std::unordered_map<std::string, int> Keyboard::valid_keys = {
    { "A", SDL_SCANCODE_A },
    { "B", SDL_SCANCODE_B },
    { "C", SDL_SCANCODE_C },
    { "D", SDL_SCANCODE_D },
    { "E", SDL_SCANCODE_E },
    { "F", SDL_SCANCODE_F },
    { "G", SDL_SCANCODE_G },
    { "H", SDL_SCANCODE_H },
    { "I", SDL_SCANCODE_I },
    { "J", SDL_SCANCODE_J },
    { "K", SDL_SCANCODE_K },
    { "L", SDL_SCANCODE_L },
    { "M", SDL_SCANCODE_M },
    { "N", SDL_SCANCODE_N },
    { "O", SDL_SCANCODE_O },
    { "P", SDL_SCANCODE_P },
    { "Q", SDL_SCANCODE_Q },
    { "R", SDL_SCANCODE_R },
    { "S", SDL_SCANCODE_S },
    { "T", SDL_SCANCODE_T },
    { "U", SDL_SCANCODE_U },
    { "V", SDL_SCANCODE_V },
    { "W", SDL_SCANCODE_W },
    { "X", SDL_SCANCODE_X },
    { "Y", SDL_SCANCODE_Y },
    { "Z", SDL_SCANCODE_Z }
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
        // it.first = "A", "B", "C", etc
        m_outputs[it.first] = keyboard_state[Keyboard::valid_keys["A"]];
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
