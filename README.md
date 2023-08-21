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
Write your code in .module files. A `top.module` file is required and this is the entry point of the simulation. To run the application do:
```
./simple-hdl [module directory] [clock speed]
```
where `[module directory]` is the folder containing all of your .module files and `[clock speed]` is the clock period in milliseconds (fixed 50% duty cycle).

### Module Syntax
Each module may have inputs, outputs, and logic variables. These are called _parameters_. Inputs are set by previous modules while logics and outputs are updated by the module itself. Logic variables are always initialized to either a one or a zero. Parameters can be created as follows: 
```
input [name]
output [name]
logic [name] [init value]
```
`[name]` can be any string without spaces that is not a keyword like input, output, logic, etc.

You can write **comments** to make your code more legible:
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
\
There are several built-in modules that can modify the values of logic and output variables.
\
A **nand** module can be instantiated like this:
```
nand [param A] [param B] [param Z]
```
where `[param A]` and `[param B]` are the names of inputs or logic variables and `[param Z]` is the name of an output or logic variable which will be set to the nand of `[param A]` and `[param B]`.

For example, a module that would compute the _not_ of a bit by doing _nand_ with 1  (A↑1 ≡ ~A) could be written like this:
```
# not.module #
input module_input
logic logic_one 1
output module_output
nand module_input logic_one module_output
```
\
A **clock** module can be instantiated like this:
```
clock [param]
```
`[param]` is the name of an output or logic variable which will be set to the current value of the clock.
\
A **keyboard** module can be instantiated like this:
```
keyboard [key] [param]
```
where `[key]` can be any letter A-Z and `[param]` is the name of an output or logic variable which will be set if and only if that key is currently pressed.
\
To instantiate a module that you have written, do:
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
\
The built-in **present** module can be used to see the value of parameters in real-time:
```
present [param] [x] [y] [r] [g] [b]`
```
This draws a rectangle to the screen at (`[x]`, `[y]`) with the color specified when `[param]` is set. Coordinates and color values go from 0 to 255.

See `example-modules` for more example modules.

## TODO

- [ ] check that modules are defined after ports/parameters
- [x] check for module ins/logics->ins, outs/logics->outs 
- [ ] disallow repeat names
- [ ] check that all inputs and outputs in module instantiation are satisfied (cannot have unconnected ports)
- [x] check for end of comment and endmodule
- [x] check for cyclic module definition
- [ ] check if parameters have been created
- [ ] check for parameter names that have been used but not created (see 1)
- [ ] do not create window and loop if no keyboard or presenter modules created
