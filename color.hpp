#pragma once
#include <SDL2/SDL.h>
#include "module.hpp"

class Color : public Module {
public:
    Color(SDL_Renderer *t_renderer, char t_red, char t_green, char t_blue);
    void evaluate() override;

private:
    SDL_Renderer *m_renderer;
    char m_red, m_green, m_blue;
    int m_x, m_y, m_width;
};
