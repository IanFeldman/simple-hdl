#include <fstream>
#include "clock.hpp"
#include "definitions.hpp"
#include "nand.hpp"
#include "presenter.hpp"
#include "simulation.hpp"

Simulation::Simulation(std::string t_directory, int t_clock_speed) {
    m_directory = t_directory;
    m_clock_speed = t_clock_speed;
    m_running = true;
    m_clock = 0;
}

void Simulation::initialize() {
    // init video and events
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Error initializing SDL video: " << SDL_GetError() << std::endl;
        return;
    }
    // create window
    m_window = SDL_CreateWindow("Simple HDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return;
    }
    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return;
    }
    std::cout << "SDL initialized" << std::endl;

    // parse modules
    Module *top_module = parseFile(createFilePath(ENTRY), TOP_MOD_NAME);
    if (top_module) {
        // begin loop
        update(top_module);
        // debug at the end
        debug();
    }
    else {
        std::cout << "Error: Failed to parse top.module" << std::endl;
    }
    shutdown();
}

Module *Simulation::parseFile(std::string t_file_name, std::string t_module_name) {
    Keyboard *keyboard;
    Module::Connection keyboard_connection; // connection from top to keyboard
    bool created_keyboard = false;

    // filestream variable file
    std::fstream file;
    std::string word;

    // opening file
    file.open(t_file_name.c_str());
 
    // error occurred while opening the file.
    if (!file.is_open()) {
        std::cout << "(" << t_file_name << ") ";
        std::cerr << "Error opening file" << std::endl;
        return nullptr;
    }

    // create module
    Module *module = new Module(t_module_name, t_file_name);
    // set is top
    if (t_module_name == TOP_MOD_NAME) {
        module->setIsTop(true);
    }
    else {
        module->setIsTop(false);
    }
    // add to simluation module list
    addModule(module);

    // extracting words from the file
    while (file >> word)
    {
        if (word == COMMENT) {
            file >> word;
            while (word != COMMENT) {
                if (!(file >> word)) {
                    std::cout << "(" << t_file_name << ") ";
                    std::cout << "Error: missing end of comment" << std::endl;
                    file.close();
                    return nullptr;
                }
            }
        }
        else if (word == INPUT) {
            std::string input_name;
            file >> input_name;
            module->addInput(input_name);
        }
        else if (word == OUTPUT) {
            std::string output_name;
            file >> output_name;
            module->addOutput(output_name);
        }
        else if (word == LOGIC) {
            std::string logic_name, logic_value;
            file >> logic_name;
            file >> logic_value;
            // check value
            int value;
            if (logic_value == "0") {
                value = 0;
            }
            else if (logic_value == "1") {
                value = 1;
            }
            else {
                std::cout << "(" << t_file_name << ") ";
                std::cout << "Error: Logic assignment must be 0 or 1" << std::endl;
                file.close();
                return nullptr;
            }
            module->addLogic(logic_name, value);
        }
        else if (word == MODULE) {
            std::string module_name, module_filename, port_name, port_value;
            // create new module
            file >> module_name;
            file >> module_filename;
            std::string file_path = createFilePath(module_filename);
            // check for cyclical module
            if (file_path == t_file_name) {
                std::cout << "(" << t_file_name << ") ";
                std::cout << "Error: Cannot instantiate module inside itself" << std::endl;
                file.close();
                return nullptr;
            }
            Module *new_module = parseFile(file_path, module_name);
            // check if module was created correctly
            if (!new_module) {
                file.close();
                return nullptr;
            }
            // create connection
            Module::Connection connection;
            connection.module = new_module;
            // create map
            std::unordered_map<std::string, std::string> port_map;
            file >> port_name;
            while (port_name != ENDMODULE) {
                if (!(file >> port_value)) {
                    std::cout << "(" << t_file_name << ") ";
                    std::cout << "Error: missing end of module" << std::endl;
                    file.close();
                    return nullptr;
                }
                port_map[port_name] = port_value; 
                file >> port_name;
            }
            connection.port_map = port_map;
            // add connection
            module->addConnection(connection);
        }
        else if (word == NAND) {
            Nand *nand = new Nand();
            addModule(nand);
            // create connection
            Module::Connection connection;
            connection.module = nand;
            // create map
            std::unordered_map<std::string, std::string> port_map;
            file >> port_map["A"]; 
            file >> port_map["B"];
            file >> port_map["Z"];
            connection.port_map = port_map;
            // add connection
            module->addConnection(connection);
        }
        else if (word == KEYBOARD) {
            if (!module->isTop()) {
                std::cout << "(" << t_file_name << ") ";
                std::cout << "Error: Can only create keyboard in top module" << std::endl;
                file.close();
                return nullptr;
            }
            // create keyboard if it doesn't exist
            if (!created_keyboard) {
                // malloc
                keyboard = new Keyboard();
                addModule(keyboard);
                // connection
                keyboard_connection.module = keyboard;
                created_keyboard = true;
            }
            std::string key, connected_port;
            file >> key;
            // check if it is a valid key
            if (Keyboard::valid_keys.find(key) == Keyboard::valid_keys.end()) {
                std::cout << "(" << t_file_name << ") ";
                std::cout << "Error: invalid keyboard key '" << key << "'" << std::endl;
                file.close();
                return nullptr;
            }
            file >> connected_port;
            keyboard_connection.port_map[key] = connected_port; 
            // add output to keyboard
            keyboard->addOutput(key);
        }
        else if (word == PRESENT) {
            std::string param, x, y, r, g, b;
            // TODO: check for stoi() error
            file >> param;
            file >> x;
            file >> y;
            file >> r;
            file >> g;
            file >> b;
            Presenter *presenter = new Presenter(m_renderer, (char)stoi(x), (char)stoi(y), (char)stoi(r), (char)stoi(g), (char)stoi(b));
            addModule(presenter);
            // create connection
            Module::Connection connection;
            connection.module = presenter;
            // create map
            std::unordered_map<std::string, std::string> port_map;
            port_map["A"] = param;
            connection.port_map = port_map;
            // add connection
            module->addConnection(connection);
        }
        else if (word == CLOCK) {
            std::string param;
            file >> param;
            // create clock
            Clock *clock = new Clock(this);
            addModule(clock);
            // create connection
            Module::Connection connection;
            connection.module = clock;
            // create map
            std::unordered_map<std::string, std::string> port_map;
            port_map["Z"] = param;
            connection.port_map = port_map;
            // add connection
            module->addConnection(connection);
        }
        else {
            std::cout << "(" << t_file_name << ") ";
            std::cout << "Error: invalid token '" << word << "'" << std::endl;
            file.close();
            return nullptr;
        }
    }

    // only want to add one connection for all keyboard outputs
    if (created_keyboard) {
        module->addConnection(keyboard_connection);
    }

    file.close();
    module->setIsTop(false);
    return module;
}

std::string Simulation::createFilePath(std::string t_module_name) {
    return m_directory + "/" + t_module_name + EXT;
}

void Simulation::debug() {
    for (Module *m : m_modules) {
        // don't do built-in modules
        if (m->isBuiltIn()) {
            continue;
        }

        std::cout << m->getName() << "(" << m->getFileName() << ")" << std::endl;

        std::cout << "  INPUTS" << std::endl;
        for (auto& it: *m->getInputs()) {
            std::cout << "    " << it.first << " : " << (*m->getInputs())[it.first] << std::endl;
        }

        std::cout << "  OUTPUTS" << std::endl;
        for (auto& it: *m->getOutputs()) {
            std::cout << "    " << it.first << " : " << (*m->getOutputs())[it.first] << std::endl;
        }

        std::cout << "  LOGICS" << std::endl;
        for (auto& it: *m->getLogics()) {
            std::cout << "    " << it.first << " : " << (*m->getLogics())[it.first] << std::endl;
        }

        std::cout << "  CONNECTIONS" << std::endl;
        for (Module::Connection c : m->getConnections()) {
            // name
            std::cout << "    " << c.module->getName() << "(" << c.module->getFileName() << ")" << std::endl;
            // iterate over ports
            for (auto& it: c.port_map) {
                std::cout << "      " << it.first << " <-> " << c.port_map[it.first] << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

void Simulation::update(Module *t_top_module) {
    int prev_time = SDL_GetTicks();

    while (m_running) {
        // check for quit
        pollQuit(); 

        // update clock
        int curr_time = SDL_GetTicks();
        if (curr_time > prev_time + m_clock_speed) { 
            if (m_clock) { m_clock = 0; }
            else { m_clock = 1; }
            prev_time = curr_time;
        }
        
        // clear screen
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(m_renderer);

        // update module values
        t_top_module->evaluate();

        // draw
        SDL_RenderPresent(m_renderer);
    }
}

void Simulation::pollQuit() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        m_running = false;
                        return;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                m_running = false;
                return;
            default:
                break;
        }
    }
}

void Simulation::shutdown() {
    for (Module *m : m_modules) {
        delete m;
    }

    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
