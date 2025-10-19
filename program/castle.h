#ifndef CASTLE_H_
#define CASTLE_H_

#include "grid_object.h"
#include "grid.h"
#include "move.h"

class Castle : public GO {

    public:

    Grid<GO>* grid;

    int health = 100;
    int speed = 1;

    Castle(int row, int col, Info* info, int index, Grid<GO>*& grid)
        : GO(row,  col, info,  index, grid),  {
            id = 'c';
        }

    void take_dmg(int dmg) override {
        health = health - dmg;
        if (health <= 0) {
            info->game_over = true;
        }
    }
};

#endif
