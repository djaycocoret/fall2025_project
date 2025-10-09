#ifndef CASTLE_H_
#define CASTLE_H_

#include "grid_object new.h"
#include "grid new.h"
#include <utility>

class Castle : public GO {
    public:

    Grid* grid;

    int health = 100;
    int speed = 1;

    Castle(int row, int column, Grid*& grid)
        : GO(row, column), grid(grid) {
            id = 'c';

        }

    int get_health() const override {
        return health;
    }

    void take_damage(int dmg) override {
        health = health - dmg;
        std::cout << "took damage, remaining health:" << health;
        if (dmg < 0) {
            //game over
            //no idea how to do this
        }
    }
};

#endif
