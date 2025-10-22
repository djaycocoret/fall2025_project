#ifndef GAME_H_
#define GAME_H_

#include "grid.h"
#include "sleep.h"
#include "owner.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "move.h"

class Game {

    Grid<GO> grid; //the grid on which GO are placed
    Player player; //player is an owner of GO
    AI ai; //ai is a subclass of Owner<GO>
    Info info; //info contains global information, which is used by the GOs and Owners
    Difficulty difficulty;

    int AMOUNT_WAVES = 5;

    public:

    Game(int rows, int cols) { // game intialises with dimensions of the board

        grid = Grid<GO>(rows, cols); //initialises the grid
        player = Player(rows, cols); //initialises the player
        ai = AI(rows, cols); //initialses the ai

        info.wave = 1; //initialises the info structure
        info.health = 100;
        info.score = 0;
        info.rows = rows;
        info.cols = cols;
        std::ifstream file("highscore.djayco"); //opens highscore file
        if (!file) {
            info.highscore = 0;
        } else {
            std::string line;
            getline(file, line);
            info.highscore = std::stoi(line);
        }
    }

    Game(int rows, int cols, int diff) { // game intialises with dimensions of the board

        grid = Grid<GO>(rows, cols); //initialises the grid
        player = Player(rows, cols); //initialises the player
        ai = AI(rows, cols); //initialses the ai

        difficulty = Difficulty(diff);

        info.wave = 1; //initialises the info structure
        info.health = 100;
        info.score = 0;
        info.rows = rows;
        info.cols = cols;
        std::ifstream file("highscore.djayco"); //opens highscore file
        if (!file) {
            info.highscore = 0;
        } else {
            std::string line;
            getline(file, line);
            info.highscore = std::stoi(line);
        }
    }

    void game_update() { //main update of the game
        tick(&ai); //first the ai will move
        tick(&player);
        ai_place(); //places after moving because otherwise is would move
        system("clear"); //clears the screen
        if (ai.is_empty() && info.enemies_placed >= 10) { //the next wave starts when 10 enemies are placed and the grid is empty
            next_wave();
        }
        this->display_info(); //displays health, wave, etc.
        this->display_ai_probs(); //displays the prob of selecting a column
        grid.print_grid();
        if (info.health <= 0) {
            info.game_over = true;
        }
        if (info.health < 50) {
            grid(info.rows - 1, info.cols/2)->change_char('c');
        }
        sleep(0.7);
    }

    void execute_move(Move& move, Owner<GO>* owner) { //move structure has relevant information. some things can only be done via the game object
        if (move.remove_obj) {
            GO* ptr = grid(move.row, move.col); //assigns a pointer to the object
            grid.delete_object(move.row, move.col); //deletes the object from the grid
            owner->update_death(move); //updates death (for ai, updates logits)
            owner->operator()(move.index_owner) = nullptr; //deletes the object from the owner
            //ai(move.index_owner) = nullptr; //hardcoded, since the towers do not need to be removed
            delete ptr; //deletes the object
        } else if (move.movement_bool) {
            move.moved_bool = grid.move_object(move); //moves via the grid
        } else if (move.shoot_bool) {
            grid(move.row_new, move.col_new)->take_dmg(grid(move.row, move.col)->get_power()); //shoots (could be done internally, but more control via this)
        }
    }

    void tick(Owner<GO>* owner) {
        for (int i = 0; i < 6; i++)  { //max agents is hard coded to six
            if (owner->operator()(i) != nullptr) {
                Move move; //return move also does something to the grid
                owner->operator()(i)->return_move(&move); //return the preferred move by the agent (the agent decides, not the ai)
                // ABOVE make it such that it draws from the distribution.
                this->execute_move(move, owner); //executes the move on the grid (move structure will be updated if the move has been executed)
                owner->operator()(i)->update_position(move); //updates the attributes of the grid object accordingly

            }
        }
    }

    void next_wave() {
        info.enemies_placed = 0; //wave starts with 0 enemies
        if (info.score >= info.wave * 80) {
            info.enemies_health++; //adaptive difficulty according to assignment
        }
        if (info.wave > AMOUNT_WAVES) {
            info.game_over = true; //after the 5th wave game is done
        }
        system("clear");
        grid.print_index_grid();
        std::cout << "enter which tower you would like to update: ";
        int upgrade_index;
        std::cin >> upgrade_index;
        if (upgrade_index >= 0 && upgrade_index < _max_agents) {
            player.upgrade_tower(upgrade_index);
        }
        info.wave++; //next wave
    }

    void ai_place() {
        bool should_placed = info.enemies_placed < 10; // more conditions if needed
        if (!ai.is_full() && should_placed) {
            int col = ai.place_enemy(); //selects which column it should place
            add_obj<Enemy>(0, col, &ai, &grid);

            info.enemies_placed ++;
            info.enemies_placed_total++;
        }
    }

    template<typename T> //template to add either enemy, tower or castle.
    void add_obj(int row, int col, Owner<GO>* owner, Grid<GO>* grid) {
        if (this->grid(row, col) != nullptr && !owner->is_full()) { //checks if there is place for the object.
            std::cout << "kanker"; //there is no place
        } else {
            int index = owner->return_first_empty_index(); //return first empty index
            T* ptr = new T(row, col, &info, index, grid); //new template object
            //grid deconstructor and game execute method deallocate memory. safe.
            this->grid(row, col) = ptr; //assigns pointer to the grid
            owner->operator()(index) = ptr; //assigns pointer to the owner
        }
    }

    void display_info() const { //speaks for itself
        std::cout << "health: ";
        std::cout << std::right << std::setw(3) << info.health;

        std::cout << " wave: ";
        std::cout << std::right << std::setw(2) << info.wave;

        std::cout << " score: ";
        std::cout << std::right << std::setw(6) << info.score;

        std::cout << " highscore: ";
        std::cout << std::right << std::setw(6) << info.highscore;

        std::cout << " enemy level: ";
        std::cout << std::right << std::setw(2) << info.enemies_health - 2; //-2, since it start with enemey health 3

        std::cout << std::endl;
    }

    void game_main() { //also speaks for itself
        start_game();
        while (!info.game_over) {
            game_update();
        }
        end_game();
    }

    void end_game() { //uses setw to set the width of the space, such that there is an equal spacing for different outcomes
        system("clear");
        std::cout << "game over man" << std::endl;
        std::cout << "remaining health: " << std::right << std::setw(4) << info.health << std::endl ;
        std::cout << std::left << std::setw(16) << "score" << ": " << std::right << std::setw(4) << info.score << std::endl;
        if (info.score > info.highscore) {
            std::ofstream file("highscore.djayco");
            file << info.score;
            info.highscore = info.score;
        }
        std::cout << std::left << std::setw(16) << "high score" << ": " <<  std::right << std::setw(4) << info.highscore << std::endl;
    }

    void start_game() {
        std::cout << "type any character and press enter to continue...";
        std::string input;
        std::cin >> input;

        this->add_obj<Castle>(19, info.cols/2, &player, &grid);

        if (input == "djayco_cheat") { //for testing purposes, left this is, since this is pretty handy
            this->add_obj<Tower>(5, 3, &player, &grid);
            this->add_obj<Tower>(5, 6, &player, &grid);
            this->add_obj<Tower>(5, 9, &player, &grid);
            this->add_obj<Tower>(5, 12, &player, &grid);
            this->add_obj<Tower>(5, 15, &player, &grid);
        } else {
            int placed = 0;
            int row, col;
            //TODO maybe add a feature that you can place 1 tower if you want to suck
            while (placed < 5) { //breaks after all towers have been placed
                system("clear");
                grid.print_grid(); //shows the grid first
                std::cout << "on which row would you like to place: ";
                std::cin >> row;
                std::cout << "on which col would you like to place: ";
                std::cin >> col;
                //if row and column are on the grid, and spot is empty
                if (row >= 0 && row <= info.rows && col >= 0 && col <= info.cols && grid(row, col) == nullptr) {
                    this->add_obj<Tower>(row, col, &player, &grid);
                    placed++;
                } else {
                    std::cout << "invalid place" << std::endl;
                    std::cout << "note that you cannot place a tower on an occupied place, outside of the grid, nor in the top two rows." << std::endl;
                    sleep(5); //pauses the thread, such that user can read
                }
            }
        }
    }

    void display_ai_probs() {
        std::vector<double> prob = ai.generate_probs();
        std::cout << "  ";
        for (int i = 0; i < info.cols; i ++) {
                std::cout << std::right << std::setw(4) <<  std::fixed << std::setprecision(2) << prob[i] << " ";
            }
            std::cout << std::endl;
    }
};


#endif
