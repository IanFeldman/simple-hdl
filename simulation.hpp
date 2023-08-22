#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "keyboard.hpp"
#include "module.hpp"

class Simulation {
public:
    Simulation(std::string t_directory, int t_clock_speed);
    void initialize();
    Module *parseFile(std::string t_file_name, std::string t_module_name);
    void addModule(Module *t_module) { m_modules.push_back(t_module); }
    std::string createFilePath(std::string t_module_name);

    void pollQuit();

    // shows current values/connections of all modules
    void debug();

    int getClock() { return m_clock; }

    // frame update
    // return 0 on success, -1 on failure
    int update(Module *t_top_module);
    void shutdown();


private:
    std::string m_directory;
    int m_clock_speed;
    std::vector<Module*> m_modules;
    bool m_running;
    int m_clock;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_is_io;
};
