#ifndef TOWER_H_
#define TOWER_H_

#include "grid new.h"
#include "grid_object new.h"
#include <cmath>
#include <iostream>

class Tower : public GO {
    Grid* grid;
    int power = 1;
    int range = 1;
    public:

    Tower(int row, int column, Grid*& grid)
        : GO(row, column), grid(grid) {
            id = 't';
        }

    void update() override {
        this->shoot();
    }

    void shoot() override {
        for (int i = row - range; i <= row + range; i++) {
            for (int j = column - range; j <= column + range; j++) {
                if ( std::sqrt( pow(i - row, 2) + pow(j - column, 2))  <= range) {
                    if (grid->operator()(i,j) != nullptr) {
                        grid->operator()(i,j)->take_damage(power);
                    }
                }
            }
        }
    }
};

#endif
