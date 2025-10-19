#ifndef GAME_H_
#define GAME_H_

#include "grid.h"
#include "tower.h"
#include "enemy.h"
#include "sleep.h"
#include "owner.h"
#include "ai.h"
#include <csignal>
#include <fstream>
#include <iomanip>
#include <vector>
#include "move.h"

class Game {

    Grid<GO> grid;
    Owner<GO> player;
    AI ai;
    Info info;


    public:

    Game(int rows, int cols) {
        grid = Grid<GO>(rows, cols);
        info.rows = rows;
        info.cols = cols;
        player = Owner<GO>();
        ai = AI();

        info.wave = 1;
        info.health = 100;
        info.score = 0;

        std::ifstream file("highscore.djayco");
        if (!file) {
            info.highscore = 0;
        } else {
            std::string line;
            getline(file, line);
            info.highscore = std::stoi(line);
        }
    }

    void execute_move(Move& move, Owner<GO>* owner) {
        if (move.remove_obj) {
            GO* ptr = grid(move.row, move.col);
            grid.delete_object(move.row, move.col);
            ai(move.index_owner) = nullptr; //hardcoded, since the towers do not need to be removed
            delete ptr;
        } else if (move.movement_bool) {
            move.moved_bool = grid.move_object(move);
        } else if (move.shoot_bool) {
            grid(move.row_new, move.col_new)->take_dmg(grid(move.row, move.col)->get_power());
        } else if (move.new_obj) {

        }
    }

    void tick(Owner<GO>* owner) {
        for (int i = 0; i < 6; i++)  { //max agents is hard coded to six
            if (owner->operator()(i) != nullptr) {
                Move move; //return move also does something to the grid
                owner->operator()(i)->return_move(&move); //return the preferred move by the agent (the agent decides, not the ai)
                this->execute_move(move, owner); //executes the move on the grid (move structure will be updated if the move has been executed)
                owner->operator()(i)->update_position(move); //updates the attributes of the grid object accordingly

            }
        }
    }

    void game_update() {
        tick(&ai);
        tick(&player);
        ai_place(); //places after moving because otherwise is would move
        system("clear");
        this->display_info();
        grid.print_grid();
        if (info.health <= 0) { //add more conditions
            info.game_over = true;
        }
        sleep(0.7);
    }

    void ai_place() {
        if (!ai.is_full()) {
            //ai behaviour here
            int col = random_int(0, info.cols - 1);

            add_obj<Enemy>(0, col, &ai, &grid);
        }
    }

    template<typename T>
    void add_obj(int row, int col, Owner<GO>* owner, Grid<GO>* grid) {
        if (this->grid(row, col) != nullptr && !owner->is_full()) {
            std::cout << "kanker";
        } else {
            int index = owner->return_first_empty_index();
            T* ptr = new T(row, col, &info, index, grid);
            //grid deconstructor and game execute method deallocate memory. safe.
            this->grid(row, col) = ptr;
            owner->operator()(index) = ptr;
        }
    }

    void display_info() const {
        std::cout << "health: ";
        std::cout << std::right << std::setw(3) << info.health;

        std::cout << " wave: ";
        std::cout << std::right << std::setw(2) << info.wave;

        std::cout << " score: ";
        std::cout << std::right << std::setw(6) << info.score;

        std::cout << " highscore: ";
        std::cout << std::right << std::setw(6) << info.highscore;

        std::cout << std::endl;
    }

    void game_loop() {
        while (!info.game_over) {
            game_update();
        }
        end_game();
    }

    void end_game() {
        system("clear");
        std::cout << "game over man" << std::endl;
        std::cout << std::left << std::setw(10) << "score" << ": " << std::right << std::setw(6) << info.score << std::endl;
        if (info.score > info.highscore) {
            std::ofstream file("highscore.djayco");
            file << info.score;
            info.highscore = info.score;
        }
        std::cout << std::left << std::setw(10) << "high score" << ": " <<  std::right << std::setw(6) << info.highscore << std::endl;
    }

    void test() {
        this->add_obj<Tower>(5, 5, &player, &grid);

        this->add_obj<Enemy>(1, 4, &ai, &grid);
        game_loop();

    }


};


#endif
