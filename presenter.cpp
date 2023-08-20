#include <SDL2/SDL.h>
#include "presenter.hpp"

Presenter::Presenter(SDL_Renderer* t_renderer, char t_x, char t_y, char t_red, char t_green, char t_blue)
    :Module("COLOR", "built-in")
{
    m_renderer = t_renderer;
    m_red = t_red;
    m_green = t_green;
    m_blue = t_blue;
    m_x = t_x;
    m_y = t_y;
    m_width = 20;

    addInput("A");
}

void Presenter::evaluate() {
    // draw color if enabled
    if (m_inputs["A"]) {
        SDL_SetRenderDrawColor(m_renderer, m_red, m_green, m_blue, 255);
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_width; j++) {
                SDL_RenderDrawPoint(m_renderer, m_x * m_width + i, m_y * m_width + j);
            }
        }
    }
}
