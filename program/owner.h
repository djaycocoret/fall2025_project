#ifndef OWNER_H_
#define OWNER_H_


#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include "sleep.h"
#include "move.h"
#include "grid_object.h"

int const _max_agents = 6; //five towers, plus one castle; six enemies

template <typename T>
class Owner {
    protected:
    std::vector<T*> agents;
    int grid_rows, grid_cols;
    int score;

    public:

    std::vector<double> prob;

    Owner() {}

    Owner(int grid_rows, int grid_cols) : grid_rows(grid_rows), grid_cols(grid_cols) {
        agents.resize(_max_agents, nullptr);
    }

    T* const operator()(int index) const {
        return agents.at(index);
    }

    T*& operator()(int index) {
        return agents.at(index);
    }

    bool is_full() const {
        bool is_full = true; //assumes is full and checks if this is the case
        for (int i = 0; i < agents.size(); i++) {
            is_full = (agents[i] != nullptr) && is_full;
        }
        return is_full;
    }

    bool is_empty() const {
        bool is_empty = true;
        for (int i = 0; i < agents.size(); i++) {
            is_empty = (agents[i] == nullptr) && is_empty;
        }
        return is_empty;
    }

    int return_first_empty_index() const {
            for (int i = 0; i < _max_agents; i++) {
            if (agents[i] == nullptr) {
                return i;
            }
        }
        return -1; //unsafe honestely, check if it has an empty spot first
    }

    std::vector<double> virtual generate_probs() {
        return {1.0}; //default stuff to shut up the compiler
    }

    void virtual update_death(Move& move) {}
};

#endif

#ifndef AI_H_
#define AI_H_

int draw_from_distribution(std::vector<double> probs) {
    double number = random_double(0,1);
    double sum = 0;
    for (int i = 0; i < probs.size(); i++) {
        sum = sum + probs[i];
        if (sum > number) {
            return i;
        }
    }
    return -1; //how do i make this prettier
}

class Player : public Owner<GO> {
    public:

    Player(int grid_rows, int grid_cols) : Owner<GO>(grid_rows, grid_cols) {}

    Player() {}

    ~Player() {}

    void upgrade_tower(int index) {
        agents[index]->upgrade_range();
    }
};

class AI : public Owner<GO> {
    public:

    double learning_rate = 0.7;
    bool done = false;
    int width_column_adjustment = 3;

    std::vector<double> logits;

    AI() : Owner<GO>() {}

    AI(int grid_rows, int grid_cols) : Owner<GO>(grid_rows, grid_cols) {
        prob.resize(grid_cols, 1.0);
    }

    ~AI() {}

    std::vector<double> generate_probs() override {
        std::vector<double> prob_output;
        prob_output.resize(grid_cols);
        double sum = 0;
        for (int i = 0; i < grid_cols; i++) {
            sum = sum + exp(this->prob[i]); //
        }

        for (int i = 0; i < grid_cols; i++) {
            prob_output[i] = exp(this->prob[i]) / sum;
        }

        return prob_output;
    }

    void update_death(Move& move) override {
        int scalar;
        if (!move.reached_castle) {
            scalar = -1;
        } else {
            scalar = 1;
        }
        int w = std::min(1, width_column_adjustment);
        for (int i = move.col - w; i < move.col + w; i++) {
            if (i >= 0 && i <= grid_cols) {
                prob[i] = prob[i] + scalar * learning_rate * 1 / (abs(i - move.col) + 1);
            }
        }
    }

    int place_enemy() {
        //warning: does not place an enemy, only return the column in which
        return draw_from_distribution(generate_probs());
    }

};

#endif
