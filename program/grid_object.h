#ifndef GRID_OBJECT_H_
#define GRID_OBJECT_H_

#include "grid.h"

class GO {
    protected:

    int row;
    int column;
    Grid& grid;
    char id = 'o';

    public:

    GO(int row, int column, Grid& grid, char id)
        : row(row), column(column), grid(grid), id(id) {
            grid(row, column) = id;
        }

    void del() {
        grid(row, column) = " ";
    }
};

#endif
