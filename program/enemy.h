#ifndef ENEMY_H_
#define ENEMY_H_

#include "grid_object.h"
#include "grid.h"
#include <utility>

class Enemy : public GO {
    public:

    Grid* grid;

    int health = 10;
    int speed = 1;
    int power = 10;

    Enemy(int row, int column, Owner<GO*>* owner, Grid* grid)
        : GO(row, column, owner), grid(grid) {
            id = 'e';
            if (owner != nullptr) {
                health = owner->get_max_health();
                //health = 100; //uncomment when hardcoding for testing
            }
        }

    void update() override {
            this->move_forward();
    }

    void move_forward() override {
        if (row+speed < grid->rows) { //so this is everything that is not the last row
            if (grid->move(row, column, row + this->speed, column)){
                row = row + this->speed;
            } else if (grid->move(row, column, row + this->speed, column-1)) {
                row = row + this->speed;
                column = column - 1;
            } else if (grid->move(row, column, row + this->speed, column+1)) {
                row = row + this->speed;
                column = column + 1;
            } else { //if it cannot move, delete
                this->remove_from_owner();
                grid->delete_object(row, column);
            }

        } else { //this is when it reaches the last row
            grid->operator()(grid->rows, (int)grid->columns/2)->take_damage(10);

            //delete pointers from both the grid and items from owner
            this->remove_from_owner();
            grid->delete_object(row, column);
        }
    }

    void take_damage(int dmg) override {
        health = health - dmg;
        if (health <= 0) {
            this->owner->return_opponent()->adjust_score(10);
            this->remove_from_owner();
            grid->delete_object(this->row, this->column);
        }
    }
};

#endif
