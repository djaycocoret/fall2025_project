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
    Owner<GO*>* player;
    Owner<GO*>* ai;
    public:

    Game(int rows, int columns, Owner<GO*>* player, Owner<GO*>* ai) : player(player), ai(ai) {
        grid = new Grid(rows, columns);
        grid->place(rows, (int)columns/2, new Castle(rows, (int)columns/2, grid));
    }

    ~Game() {
        delete grid;
    }

    template<typename T>
    void place_object(int row, int column, Owner<GO*>* owner) {
        T* obj = new T(row, column, owner, grid);
        grid->place(row, column, obj);
        owner->add_object(obj);
    }

    void update() {
        grid->update();
        grid->print_grid(player);
        player->print_objects();
        sleep(2);
    }
};

#endif
