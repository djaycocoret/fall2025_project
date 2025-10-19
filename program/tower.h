#ifndef TOWER_H_
#define TOWER_H_

#include "grid.h"
#include "grid_object.h"
#include <cmath>
#include <iostream>

class Tower : public GO {
    int range;

    public:

    Tower(int row, int col, Info* info, int index, Grid<GO>* grid)
    : GO(row, col, info, index, grid) {
        id = 'T';
        range = 3;
    }


    void return_move(Move* move) override {
        for (int i = std::max(0, row - range); i <= std::min(info->rows - 1, row + range); i++) {
            for (int j = std::max(0, col - range); j <= std::min(info->cols - 1, col + range); j++) {
                if ( std::sqrt( pow(i - row, 2) + pow(j - col, 2))  <= range) {
                    if (grid->operator()(i,j) != nullptr && grid->operator()(i,j)->get_id() == 'e'   ) {
                            //grid->operator()(i,j)->take_dmg(power);
                            move->row_new = i;
                            move->col_new = j;
                            move->row = row;
                            move->col = col;
                            move->shoot_bool = true;
                    }
                }
            }
        }
    }
};

#endif
