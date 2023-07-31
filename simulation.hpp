#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "keyboard.hpp"
#include "module.hpp"

class Simulation {
public:
    Simulation(std::string t_directory);
    void initialize();
    Module *parseFile(std::string t_file_name, std::string t_module_name);
    void addModule(Module *t_module) { m_modules.push_back(t_module); }
    std::string createFilePath(std::string t_module_name);

    void pollQuit();

    // shows current values/connections of all modules
    void debug();

    // frame update
    void update(Module *t_top_module);
    void shutdown();

private:
    // key: key, value: input name
    std::unordered_map<std::string, std::string> m_key_input_map;
    std::string m_directory;
    std::vector<Module*> m_modules;
    Keyboard *m_keyboard;
    bool m_created_keyboard;
    bool m_running;
    int m_clock;
    SDL_Window *m_window;
};
