# Simple HDL
Create your own single-bit logical connections with this basic hardware description language. Built-in features include nand logic, variable clock, keyboard input, and display output. 

## Dependencies
- Git
- C++ Compiler (gcc, ...)
- SDL2 Library

On MacOS:
```
brew install git sdl2
```

*g++ can be installed through the mac command line developer tools*

## Build Instructions
```sh
# Clone this repo
git clone https://github.com/IanFeldman/simple-hdl.git
cd simple-hdl

# Create a build folder
mkdir build
cd build

# Build (g++ on MacOS)
g++ *.cpp -std=c++11 -ISDL2/include -LSDL2/lib -lSDL2-2.0.0 -o simple-hdl
(or run make)
```

## Usage:
### Modules
Write your code in .module files. A `top.module` file is required and this is the entry point of the simulation.
To run the application do:
```
./simple-hdl [module directory] [clock speed]
```
where `[module directory]` is the folder containing all of your .module files and `[clock speed]` is the clock period in milliseconds (fixed 50% duty cycle).

### Module Syntax
#### Parameters
Each module may have input, output, and logic variables called parameters. Inputs are set by previous modules while logics and outputs are updated by the module itself. Logic variables are always initialized to either a one or a zero. Parameters can be defined as follows: 
```
input [name]
output [name]
logic [name] [init value]
```
`[name]` can be any string without spaces that is not a keyword like input, output, logic, etc.

#### Comments
Comments will be ignored.
```
# comments are written like this #
```
```
#
they can
also be
multi-line
#
```

#### Built-in Modules
There are several built-in modules that can modify the values of logic and output variables.

##### Nand
```
nand [param A] [param B] [param Z]
```
where `[param A]` and `[param B]` are the names of input or logic variables and `[param Z]` is the name of an output or logic variable which will be assigned the result of `[param A]` nand `[param B]`.

For example, a module that would compute the _not_ of a bit by doing _nand_ with 1 (A↑1 ≡ ~A) could be written like this:
```
# not.module #
input module_input
logic logic_one 1
output module_output
nand module_input logic_one module_output
```

##### Clock
```
clock [param]
```
`[param]` is the name of an output or logic variable which will be set to the current value of the clock.

##### Keyboard
```
keyboard [key] [param] [toggle]
```
where `[key]` can be any letter A-Z and `[param]` is the name of an output or logic variable which will be set if and only if that key is currently pressed.  `[toggle]` is a binary value that indicates whether the parameter will be toggle-enabled or not. When `[toggle]` is 0, the associated parameter will enable only while the key is held down and disable once it is let up. When it is 1, the associated parameter will become enabled once the key is pressed and stay enabled until the key is pressed again. 

*Note*: the keyboard can only be used in top.module

##### Present
This module does not modify parameters, but can be used to see the their valuesin real-time:
```
present [param] [x] [y] [r] [g] [b]`
```
This draws a square to the screen at (`[x]`, `[y]`) with the color specified when `[param]` is set. Coordinates and color values range from 0 to 255 inclusive.

#### User-Defined Modules
To use a module that you have written, do:
```
module [name] [filename] [input name] [param] [input name] [param] ... [output name] [param] [output name] [param] ... endmodule
```
Again, `[name]` can be any non-keyword string without spaces. `[filename]` is the module filename _without_ the .module extension. Then specify which parameters should be passed into each input and which parameters the module should output to. `[input name]` and `[output name]` come from the module you are instantiating and the amount of each is determined by that module.

For example, to use the `not.module ` we created before, do:
```
# example.module #
input A
output Z
module my_not_module not module_input A module_output Z endmodule
```
This module has input A and output Z. It then calls the sub-module my_not_module and passes A into its input (module_input) and passes its output (module_output) into Z.

See `example-modules` for more example modules.

### Window
The application window can be resized and moved. Close with the red x in the corner or hit `esc`. The window will not be created if no keyboard, presenter, or clock modules are created. The program always prints out debug information at the end detailing what modules were used, how they were connected, and the final values of their parameters.

## Dev TODO

- [x] check that parameters used were defined 
- [x] check for module ins/logics->ins, outs/logics->outs 
- [ ] disallow repeat names
- [ ] check that all inputs and outputs in module instantiation are satisfied (cannot have unconnected ports)
- [x] check for end of comment and endmodule
- [x] check for cyclic module definition
- [ ] check if parameters have been created
- [ ] check for parameter names that have been used but not created (see 1)
- [x] do not create window or loop if no keyboard, presenter or clock modules created
- [ ] handle stoi() errors
- [x] option to toggle keyboard input
- [ ] assign module (copies value from one parameter to another)
- [ ] print error line
