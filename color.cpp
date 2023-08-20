#include <SDL2/SDL.h>
#include "color.hpp"

Color::Color(SDL_Renderer* t_renderer, char t_red, char t_green, char t_blue)
    :Module("COLOR", "built-in")
{
    m_renderer = t_renderer;
    m_red = t_red;
    m_green = t_green;
    m_blue = t_blue;
    m_x = 10;
    m_y = 10;
    m_width = 10;

    addInput("A");
}

void Color::evaluate() {
    // draw color if enabled
    if (m_inputs["A"]) {
        SDL_SetRenderDrawColor(m_renderer, m_red, m_green, m_blue, 255);
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_width; j++) {
                SDL_RenderDrawPoint(m_renderer, m_x + i, m_y + j);
            }
        }
        // TODO: add width in here
    }
}
