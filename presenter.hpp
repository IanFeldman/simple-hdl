#pragma once
#include <SDL2/SDL.h>
#include "module.hpp"

class Presenter : public Module {
public:
    Presenter(SDL_Renderer *t_renderer, char t_x, char t_y, char t_red, char t_green, char t_blue);
    int evaluate() override;

private:
    SDL_Renderer *m_renderer;
    char m_red, m_green, m_blue;
    int m_x, m_y, m_width;
};
