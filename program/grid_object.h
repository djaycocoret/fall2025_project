#ifndef GRID_OBJECT_H_
#define GRID_OBJECT_H_

#include <iostream>
#include <string>
#include "owner.h"



class GO {
    protected:

    int row;
    int column;


    bool turn = false;
    Owner<GO*>* owner;

    public:



    int index_thing;

    char id = 'o';
    int health;

    GO(int row, int column, Owner<GO*>* owner = nullptr)
        : row(row), column(column), owner(owner) {}

    virtual ~GO() {}

    void remove_from_owner() {
        owner->return_death(this->row, this->column);
        owner->delete_from_items(index_thing);
    }

    virtual void move_to(int row_new, int column_new) {}

    virtual void print() const {
        std::cout << row << ", " << column << std::endl;
    }

    virtual void take_damage(int dmg) {}

    virtual void shoot() {}

    virtual void move_forward() {}

    virtual Owner<GO*>* return_owner() {
        return owner;
    }

    void set_index(int i) {
        index_thing = i;
    }

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

    template<typename K>
    bool operator!=(const K& other) const {
        return other != nullptr;
    }
};

#endif
