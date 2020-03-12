# Todo

A basic list of some things that need to be done.

## Compiler

Things that the compiler needs to write a full program.

- [ ] Verion X.X complete. Must compile everything in "Documents/Examples".
  - [ ] Math
    - [ ] Plus
    - [ ] Minus
    - [ ] Times
    - [ ] Divide
    - [ ] Order of operations.
  - [ ] Standard libary.
    - [ ] Memory
      - [ ] new/malloc
      - [ ] delete/free
    - [ ] Containers
      - [ ] Array
      - [ ] Vector
      - [ ] Map/Hash map
    - [ ] Regx
  - [ ] Function calls
    - [ ] Pass function params
  - [ ] Multiable files in a program.
  - [ ] Veriable sizes
    - [ ] 1 byte (char)
    - [ ] 4 bytes (int)
    - [ ] 8 bytes (int64)
    - [ ] 4 bytes (float)
    - [ ] 8 bytes (double)
  - [ ] Use VM stack space.
  - [ ] Language
    - [ ] Loops
      - [ ] For
      - [ ] For each
      - [ ] While
    - [ ] Functions
      - [ ] Params
      - [ ] Function pointer.
      - [ ] Lambdas
    - [ ] Structures
      - [ ] Inheritance
      - [ ] Mutaions
    - [ ] Pointers
    - [ ] Veriable types
      - [ ] Int
      - [ ] Char
      - [ ] Strings (needs pointers)
      - [ ] Float
      - [ ] Double
    - [ ] Local scope
    - [ ] Virtual structures
    - [ ] Templates (This is a big maybe!)
    - [ ] Inline ASM
  - [ ] Command line arguments
    - [ ] Out put file name.
    - [ ] Compile as program or library
  - [ ] Deal with endianness
  - [ ] Maybe some other stuff when I get here.

## VM Core

Things that need to be done for the core of the VM

### Core
  - [ ] Deal with endianness

### OP codes

OP codes that should be added.

  - [ ] Shift left
  - [ ] Shift right
  - [ ] Give Memory
  - [ ] Free Memory
  - [ ] Keyboard/Mouse input

## Virtual Machine
  - [ ] Seperate the virtual CPU out of VM
  - [ ] Display
    - [ ] Terminal display
      - [ ] Colour
        - [ ] Forground
        - [ ] Background
      - [ ] Position (Don/t think this is needed)
    - [ ] SDL2 virtual terminal
      - [ ] Text display
      - [ ] Different fonts
      - [ ] Colour
        - [ ] Forground
        - [ ] Background
      - [ ] Resizable window.
  - [ ] Harddrive
    - [ ] Working dir.
    - [ ] System files and folders
  - [ ] Network
    - [ ] TCP
    - [ ] UDP
  - [ ] Command line arguments
    - [ ] Terminal size
    - [ ] Useable ram
    - [ ] Number of cpu cores to use (each one is a thread and share ram)
    - [ ] Use text or SDL2 for display

## Miscellaneous

 - [ ] Write lanauge standard
   - [ ] Loops
     - [ ] For
     - [ ] For each
     - [ ] While
   - [ ] Functions
     - [ ] Params
     - [ ] Function pointer.
     - [ ] Lambdas
   - [ ] Structures
     - [ ] Inheritance
     - [ ] Mutaions
   - [ ] Pointers
   - [ ] Veriable types
     - [ ] Int
     - [ ] Char
     - [ ] Strings (needs pointers)
     - [ ] Float
     - [ ] Double
   - [ ] Local scope
   - [ ] Virtual structures
   - [ ] Templates (This is a big maybe!)
   - [ ] Inline ASM
 - [ ] Documentation of design
   - [ ] VM
     - [ ] CPU
     - [ ] Display
       - [ ] Terminal
         - [ ] Colours
       - [ ] SDL2
     - [ ] OP codes
     - [ ] Input
     - [ ] Network
     - [ ] Harddrive
   - [ ] Compiler
     - [ ] How a file is parsed
     - [ ] How the AST is traversed.
     - [ ] How the AST is converted into OP codes
   - [ ] File formats.
     - [ ] Compiled program lolc
     - [ ] Compiled library ????
 - [ ] Comment code for doxygen generation. (This will for ever be ongoing.)

## Pipe dreams

1. Embedding within c/c++ programs
  1. Accessing c/c++ functions and data.
  2. C/C++ calling and accessing script functions and data.
3. Dynamically loaded library or lua script for file output on compiler.
4. Dynamically loaded library or lua script for parsing the incoming files.
  - This Is more so the compiler can compile other languages. This should generate an AST the compiler knows.
