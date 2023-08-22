#include <SDL2/SDL.h>
#include <stdio.h>
#include "keyboard.hpp"

#include <iostream>

Keyboard::Keyboard()
    :Module("KEYBOARD", "built-in")
{
    m_is_built_in = true;
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
    // get keyboard state
    const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

    // iterate over outputs
    for (auto& it : m_outputs) {
        // it.first = "A", "B", "C", etc
        std::string key = it.first;
        int scancode = Keyboard::valid_keys[key];
        int key_pressed = keyboard_state[scancode];

        // check if it is toggle-enabled
        if (m_toggle_enabled.count(key)) {
            // reenable toggling if key is up
            if (!m_toggle_enabled[key] && !key_pressed) {
                m_toggle_enabled[key] = true;
            }
            else if (m_toggle_enabled[key] && key_pressed) {
                m_outputs[key] = !m_outputs[key];
                m_toggle_enabled[key] = false; // disallowing toggling until key is released
            }
        }
        else {
            m_outputs[key] = key_pressed;
        }
    }
}
