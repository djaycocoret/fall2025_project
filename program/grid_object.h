#ifndef GRID_OBJECT_H_
#define GRID_OBJECT_H_

#include <iostream>
class GO {
    protected:

    int row;
    int column;
    bool turn = true;

    public:

    char id = 'o';
    int health;

    GO(int row, int column)
        : row(row), column(column) {
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

};

#endif
