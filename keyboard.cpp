#include <SDL2/SDL.h>
#include <stdio.h>
#include "keyboard.hpp"

Keyboard::Keyboard()
    :Module("KEYBOARD", "built-in")
{
}

const std::unordered_set<std::string> Keyboard::valid_keys = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
};

void Keyboard::evaluate() {
    // clear outputs
    for (auto& it: m_outputs) {
        m_outputs[it.first] = 0;
    }

    // poll for keyboard events
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_KEYDOWN:
                m_outputs[SDL_GetKeyName(event.key.keysym.sym)] = 1;
                break;
            default:
                break;
        }
    }
}
