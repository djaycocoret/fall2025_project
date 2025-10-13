#ifndef GAME_H_
#define GAME_H_

#include "grid.h"
#include "tower.h"
#include "enemy.h"
#include "castle.h"
#include "sleep.h"
#include "owner.h"
#include <csignal>
#include <fstream>
#include <iomanip>
#include <vector>


class Game {
    bool generate = true;
    Grid* grid;
    Owner<GO*>* player;
    Owner<GO*>* ai;
    int high_score;

    int enemies_placed = 0;
    int wave = 1;
    public:

    bool game_over_thing = false;

    Game(int rows, int columns, Owner<GO*>* player, Owner<GO*>* ai) : player(player), ai(ai) {
        grid = new Grid(rows, columns);
        grid->place(rows, (int)columns/2, new Castle(rows, (int)columns/2, grid, player));
        player->set_dimensions(grid->rows, grid->columns);
        ai->set_dimensions(grid->rows, grid->columns);
        high_score = load_highscore();
        grid->give_highscore(high_score);

    }

    ~Game() {
        delete grid;
    }

    int load_highscore() {
        std::ifstream file("highscore.djayco");
        if (!file) {
            return -1;
        } else {
            std::string line;
            getline(file, line);
            return std::stoi(line);
        }
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
        if (enemies_placed >= 10) {
            generate = false;
        }
        if (ai->is_empty() && !generate) {
            wave++;
            if (player->get_score() >= wave * 80) {
                ai->add_max_health(1);
            }
            enemies_placed = 0;
            generate = true;
            ai->add_max_health(1);
        }
        if (wave > 5) {
            this->game_over_thing = true;
        }
        if (!this->game_over_thing) {
            int* column = new int;
            *column = -1;
            ai->make_move(column);
            if (*column > 0 && enemies_placed < 10 && generate) {
                this->place_object<Enemy>(1, *column, ai);
                enemies_placed++;
            }
            delete column;
            player->make_move(nullptr); //shoots
            ai->generate_probs();
            std::vector<double>* ptr = new std::vector<double>;;
            *ptr = ai->generate_probs();
            grid->print_grid(player,true,  &wave, ptr);
            delete ptr;
            std::cout << std::endl;
            player->print_objects();
            ai->print_objects();

        } else {
            system("clear");
            std::cout << "game over man" << std::endl;
            int score = player->get_score();
            std::cout << std::left << std::setw(10) << "score" << ": " << std::right << std::setw(6) << score << std::endl;
            if (score > high_score) {
                std::ofstream file("highscore.djayco");
                file << score;
                high_score = score;
            }
            std::cout << std::left << std::setw(10) << "high score" << ": " <<  std::right << std::setw(6) << high_score << std::endl;

            //how to break??
        }
    }
};

#endif
