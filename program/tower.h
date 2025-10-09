#ifndef TOWER_H_
#define TOWER_H_

#include "grid.h"
#include "grid_object.h"
#include <cmath>
#include <iostream>

class Tower : public GO {
    Grid* grid;
    int power = 1;
    int range = 3;
    public:

    Tower(int row, int column, Grid*& grid)
        : GO(row, column), grid(grid) {
            id = 't';
        }

    void update() override {
        this->shoot();
    }

    void shoot() override {
        for (int i = std::max(1, row - range); i <= std::min(grid->rows, row + range); i++) {
            for (int j = std::max(1, column - range); j <= std::min(grid->columns, column + range); j++) {
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
