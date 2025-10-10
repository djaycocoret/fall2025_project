#ifndef CASTLE_H_
#define CASTLE_H_

#include "grid_object.h"
#include "grid.h"
#include <utility>

class Castle : public GO {

    public:

    Grid* grid;

    int health = 9;
    int speed = 1;

    Castle(int row, int column, Grid*& grid, Owner<GO*>* owner)
        : GO(row, column, owner), grid(grid) {
            id = 'c';

        }

    int get_health() const override {
        return health;
    }

    void take_damage(int dmg) override {
        health = health - dmg;
        if (health <= 0) {
            owner->set_game_over(true);
        }
    }

};

#endif
