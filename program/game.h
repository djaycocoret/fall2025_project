#ifndef GAME_H_
#define GAME_H_

#include "grid.h"
#include "tower.h"
#include "enemy.h"
#include "castle.h"
#include "sleep.h"
#include "owner.h"
#include <iomanip>


class Game {
    bool game_over_thing = false;
    Grid* grid;
    Owner<GO*>* player;
    Owner<GO*>* ai;
    public:

    Game(int rows, int columns, Owner<GO*>* player, Owner<GO*>* ai) : player(player), ai(ai) {
        grid = new Grid(rows, columns);
        grid->place(rows, (int)columns/2, new Castle(rows, (int)columns/2, grid, player));
    }

    ~Game() {
        delete grid;
    }

    template<typename T>
    void place_object(int row, int column, Owner<GO*>* owner) {
        T* obj = new T(row, column, owner, grid);
        grid->place(row, column, obj);
        for (int i = 0; i < 5; i++) {
            if (owner->get_items(i) == nullptr) {
                owner->set_item(obj, i); //when deleting item be carefull with pointers
                obj->set_index(i);
                return;
            }
        }
    }


    void update() {
        bool new_game_over = player->get_game_over() || ai->get_game_over();
        bool show_end_screen = (new_game_over != game_over_thing);
        game_over_thing = new_game_over;
        if (!this->game_over_thing) {

            //grid->update();

            //above should be replaced with
            //
            int* column = new int;
            if (ai->make_move(column) > 0) {
                this->place_object<Enemy>(1, *column, ai);
            }
            player->make_move(nullptr); //shoots

            grid->print_grid(player);
            std::cout << std::endl;
            player->print_objects();
            ai->print_objects();
            sleep(1);
        } else {
            system("clear");
            std::cout << "game over man" << std::endl;
            std::cout << std::left << std::setw(10) << "score" << ": " << std::right << std::setw(6) << player->get_score() << std::endl;
            std::cout << std::left << std::setw(10) << "high score" << ": " <<  std::right << std::setw(6) << "123456" << std::endl;

            //how to break??
        }
    }
};

#endif
