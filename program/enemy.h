#ifndef ENEMY_H_
#define ENEMY_H_

#include "grid_object.h"
#include "grid.h"
#include <utility>

class Enemy : public GO {
    int speed;

    public:

    Enemy(int row, int col, Info* info, int index, Grid<GO>* grid)
    :GO(row, col, info, index, grid) {
        id = 'e';
        health = 3;
        speed = 1;
    }

    void return_move(Move* move) override {
        if (health <= 0) {
            move->remove_obj = true;
            move->row = row;
            move->col = col;
            move->index_owner = index;
            info->score = info->score + 10;
        } else if (row + speed < grid->get_rows()) {
            if (grid->operator()(row+speed, col) == nullptr) {
                move->movement_bool = true;
                move->row = row;
                move->col = col;
                move->row_new = row+speed;
                move->col_new = col;
            } else if (grid->operator()(row+speed, col + 1) == nullptr) {
                move->movement_bool = true;
                move->row = row;
                move->col = col;
                move->row_new = row+speed;
                move->col_new = col + 1;
            } else if (grid->operator()(row+speed, col - 1) == nullptr) {
                move->movement_bool = true;
                move->row = row;
                move->col = col;
                move->row_new = row+speed;
                move->col_new = col - 1;
            } else { //if it cannot move, it will delete itself
                move->remove_obj = true;
                move->row = row;
                move->col = col;
                move->index_owner = index;
            }
        } else { //implies has health and the expected row will be bigger than the last row
            move->remove_obj = true;
            move->row = row;
            move->col = col;
            move->index_owner = index;
            info->health = info->health - 10;
        }
    }
};


#endif
