#ifndef GAME_H_
#define GAME_H_

#include "grid.h"
#include "tower.h"
#include "enemy.h"
#include "castle.h"
#include "sleep.h"
#include "owner.h"


class Game {
    Grid* grid;
    Owner* player;
    public:

    Game(int rows, int columns, Owner* player) : player(player) {
        grid = new Grid(rows, columns);
        grid->place(rows, (int)columns/2, new Castle(rows, (int)columns/2, grid));
    }

    ~Game() {
        delete grid;
    }

    template<typename T>
    void place_object(int row, int column, Owner* owner) {
        grid->place(row, column, new T(row, column, owner, grid));
    }

    void update() {
        grid->update();
        grid->print_grid(player);
        sleep(2);
    }
};

#endif
