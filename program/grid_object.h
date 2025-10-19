#ifndef GRID_OBJECT_H_
#define GRID_OBJECT_H_

#include <iostream>
#include <string>
#include "move.h"
#include "grid.h"

class GO {
    protected:

    int row, col; //index in grid (starting at 0)
    int index; //index in owner vector
    int health;
    char id = 'd';
    int power = 1;
    Info* info;
    Grid<GO>* grid;

    public:

    GO(int row, int col, Info* info, int index, Grid<GO>* grid)
    : row(row), col(col), info(info), index(index), grid(grid) {}

    void virtual return_move(Move* move) { //make this empty and overload in child classes
    }


    void update_position(Move& move) {
        if (move.moved_bool) {
            this->row = move.row_new;
            this->col = move.col_new;
        }
    }

    std::string return_cords() const {
        return "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
    }

    void virtual take_dmg(int dmg) {
        health = health - dmg;
    }

    int get_power() {
        return power;
    }

    char get_id() const {
        return id;
    }

};

#endif
