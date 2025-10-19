#ifndef OWNER_H_
#define OWNER_H_


#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include "sleep.h"
#include "move.h"

int const _max_agents = 6; //five towers, plus one castle; six enemies

template <typename T>
class Owner {
    protected:
    std::vector<T*> agents;
    int grid_rows, grid_cols;
    int score;

    public:

    Owner() {
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

    int return_first_empty_index() const {
            for (int i = 0; i < _max_agents; i++) {
            if (agents[i] == nullptr) {
                return i;
            }
        }
        return -1; //unsafe honestely, check if it has an empty spot first
    }

    std::vector<double> virtual generate_probs() {}

    void virtual update() {}
};

#endif
