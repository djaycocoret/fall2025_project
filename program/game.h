#ifndef GAME_H_
#define GAME_H_

#include "grid.h"
#include "tower.h"
#include "enemy.h"
#include "castle.h"
#include "sleep.h"


class Game {
    Grid* grid;
    public:

    Game(int rows, int columns) {
        grid = new Grid(rows, columns);
        grid->place(rows, (int)columns/2, new Castle(rows, (int)columns/2, grid));
    }

    ~Game() {
        delete grid;
    }

    template<typename T>
    void place_object(int row, int column) {
        grid->place(row, column, new T(row, column, grid));
    }

    void update() {
        grid->update();
        grid->print_grid();
        sleep(2);
    }
};

#endif
