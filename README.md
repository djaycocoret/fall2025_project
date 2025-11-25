# C/C++ project for cognitive science and artificial intelligence minor course

This is a game made for partial fulfillment of the cognitive science and artificial intelligence bachelor's program at Tilburg University.
While I have ported performance critical code from Python to C++ before, this was my first project fully conceptualised and programmed using C++.

## Installation

Use a C++ compiler to compile the code, I use g++.

```zsh
g++ main.cpp -o [name]
```

This will generate two warnings.

And run the program

```zsh
./[name]
```

Alternatively, you could use CMake to compile the program.
Run  the following in your terminal to build the program.

```zsh
CMake -B build && cd build && make
```

This will generate two warnings.

And to run the program

```zsh
./TOWER_DEFENSE
```

## Running the game

Press any key and enter to continue, or type in 'djayco_cheat' and hit enter to place 5 towers relatively spread out.

If chosen the former option, enter a row followed by a column. Repeat till placed 5 towers.

## About

This project was made by Djayco Coret, finished 19 November 2025.
All code is open source and can be adapted, extended, or otherwise in any way.
I do not hold any responsibility for damage to your system.
