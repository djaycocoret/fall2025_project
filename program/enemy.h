#ifndef ENEMY_H_
#define ENEMY_H_

#include "grid_object.h"
#include "grid.h"
#include <utility>

class Enemy : public GO {
    public:

    Grid* grid;

    int health = 1;
    int speed = 1;
    int power = 10;

    Enemy(int row, int column, Owner* owner, Grid*& grid)
        : GO(row, column, owner), grid(grid) {
            id = 'e';
            if (owner != nullptr) {
                health = owner->get_max_health();
            }

        }

    void update() override {
        if (turn) {
            this->move_forward();
            turn = false;
        }
    }

    void move_forward() override {
        if (row+speed <= grid->rows) {
            grid->move(row, column, row + this->speed, column);
            row = row + this->speed;
        } else {
            std::cout << "____" << row << " " << speed << std::endl;
            std::cout << "dead";
            grid->operator()(grid->rows, (int)grid->columns/2)->take_damage(10);
            grid->delete_object(row, column);
        }
    }

    void take_damage(int dmg) override {
        health = health - dmg;
        if (health <= 0) {
            this->owner->return_opponent()->adjust_score(10);
            grid->delete_object(this->row, this->column);
        }
    }
};

#endif
