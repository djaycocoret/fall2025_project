#ifndef GRID_OBJECT_H_
#define GRID_OBJECT_H_

#include <iostream>
#include <string>
#include "move.h"
#include "grid.h"
#include "sleep.h"

class GO {
    protected:

    int row, col; //index in grid (starting at 0)
    int index; //index in owner vector
    int health;
    char id = 'd'; //default id
    int power = 1;
    Info* info; //info is needed to update score and health
    Grid<GO>* grid; //tower needs the grid to scan for enemies

    public:

    GO(int row, int col, Info* info, int index, Grid<GO>* grid)
    : row(row), col(col), info(info), index(index), grid(grid) {}

    void virtual return_move(Move* move) { //make this empty and overload in child classes
    }


    void update_position(Move& move) {
        if (move.moved_bool) { //updates the attributes iff
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

    void virtual upgrade_range() {}

    int get_power() {
        return power;
    }

    char get_id() const {
        return id;
    }

    int get_index() const {
        return index;
    }

    void change_char(char input) {
        this->id = input;
    }

};

class Enemy : public GO {
    int speed;

    public:

    Enemy(int row, int col, Info* info, int index, Grid<GO>* grid)
    :GO(row, col, info, index, grid){
        id = 'e';
        this->health = info->enemies_health;
        if (info->enemies_placed % 10 == 0) {
            speed = 3;
            id = 'E';
        } else if (info->enemies_placed % 5 == 0) {
            speed = 2;
            id = 'E';
        } else {
            speed = 1;
            id = 'e';
        }
    }

    void return_move(Move* move) override { //changes move, return move is the old name
        //below basic information about the move
        move->row = row;
        move->col = col;
        move->index_owner = index;
        if (health <= 0) {
            move->remove_obj = true;
            info->score = info->score + 10;
        } else if (row + speed < grid->get_rows()) { //checks if before the final row
            //so this is kinda messy, but it works
            if (grid->operator()(row+speed, col) == nullptr) {
                move->movement_bool = true;
                move->row_new = row+speed;
                move->col_new = col;
            } else if (grid->operator()(row+speed, col + 1) == nullptr) { //TODO maybe add something such that it can draw from dist
                move->movement_bool = true;
                move->row_new = row+speed;
                move->col_new = col + 1;
            } else if (grid->operator()(row+speed, col - 1) == nullptr) {
                move->movement_bool = true;
                move->row_new = row+speed;
                move->col_new = col - 1;
            } else { //if it cannot move, it will delete itself
                move->remove_obj = true;
            }
        } else { //implies has health and the expected row will be bigger than the last row
            move->remove_obj = true;
            move->reached_castle = true;
            info->health = info->health - 10;
        }
    }
};

class Tower : public GO {
    int range;

    public:

    Tower(int row, int col, Info* info, int index, Grid<GO>* grid)
    : GO(row, col, info, index, grid) {
        id = 't';
        range = 3;
    }

    void upgrade_range() override {
        this->range = this->range + 2;
        this->id = 'T';
    }

    void return_move(Move* move) override {
        for (int i = std::max(0, row - range); i <= std::min(info->rows - 1, row + range); i++) {
            for (int j = std::max(0, col - range); j <= std::min(info->cols - 1, col + range); j++) {
                if ( std::sqrt( pow(i - row, 2) + pow(j - col, 2))  <= range) {
                    if (grid->operator()(i,j) != nullptr && (grid->operator()(i,j)->get_id() == 'e' || grid->operator()(i,j)->get_id() == 'E') ) {
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

class Castle : public GO {

    public:

    Grid<GO>* grid;

    Castle(int row, int col, Info* info, int index, Grid<GO>*& grid)
        : GO(row,  col, info,  index, grid)  {
            id = 'C';
        }
};

#endif
