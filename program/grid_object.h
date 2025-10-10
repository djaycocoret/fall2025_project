#ifndef GRID_OBJECT_H_
#define GRID_OBJECT_H_

#include <iostream>
#include <string>
#include "owner.h"

class GO {
    protected:

    int row;
    int column;
    bool turn = true;
    Owner<GO*>* owner;

    public:

    char id = 'o';
    int health;

    GO(int row, int column, Owner<GO*>* owner = nullptr)
        : row(row), column(column), owner(owner) {
        }

    virtual ~GO() {}

    virtual void move_to(int row_new, int column_new) {}

    virtual void print() const {
        std::cout << row << ", " << column << std::endl;
    }

    virtual void take_damage(int dmg) {}

    virtual void shoot() {}

    virtual void move_forward() {}

    virtual int get_health() const {
        return 0;
    }

    virtual void update() {}

    virtual void end_turn() {
        turn = true;
    }

    std::string get_position() {
        return "(" + std::to_string(row) + ", " + std::to_string(column) + ")";
    }

};

#endif
