#ifndef AI_H_
#define AI_H_

#include "owner.h"
#include "grid_object.h"
#include "sleep.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

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

class AI : public Owner<GO> {
    public:

    std::vector<double> prob;

    double learning_rate = 0.7;
    bool done = false;
    int width_column_adjustment = 2; //where zero i just the column where stuff happened


    AI() : Owner<GO>() {
        prob.resize(grid_cols, 1.0);
    }

    ~AI() {}

    std::vector<double> generate_probs() override {
        std::vector<double> prob_output;
        prob_output.resize(grid_cols);
        double sum = 0;
        for (int i = 0; i < grid_cols; i++) {
            sum = sum + exp(prob[i]); //
        }

        for (int i = 0; i < grid_cols; i++) {
            prob_output[i] = exp(prob[i]) / sum;
        }

        return prob_output;
    }

    void set_width(int width) {
        width_column_adjustment = width;
    }

    void update() override {
        for (int i = 0; i < 6; i++) {
            if (agents[i] == nullptr) {
                //
            }
        }
    }

};


#endif
