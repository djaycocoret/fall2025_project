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

class AI : public Owner<GO*> {
    public:

    double learning_rate = 0.7;
    bool done = false;
    int width_column_adjustment = 2; //where zero i just the column where stuff happened


    AI() : Owner<GO*>() {
        max_health = 3;
        name = "AI";
    }

    ~AI() {}

    std::vector<double> generate_probs() override {
        std::vector<double> prob_output;
        prob_output.resize(columns);
        double temprature = 5;
        double sum = 0;
        for (int i = 0; i < columns; i++) {
            sum = sum + exp(prob[i]); //
        }

        for (int i = 0; i < columns; i++) {
            prob_output[i] = exp(prob[i]) / sum;
        }

        return prob_output;
    }

    void return_death(int row, int column) override {
        deaths.push_back(Coordinate(row, column));
    }

    void set_width(int width) {
        width_column_adjustment = width;
    }

    void update_moves(int column, bool killed) override {
        int scalar;
        if (killed) {
            scalar = -1;
        } else {
            scalar = 1;
        }
        for (int i = column - width_column_adjustment; i < column + width_column_adjustment; i++) {
            if (i >= 0 && i <= columns) {
                prob[i] = prob[i] + scalar * learning_rate * 1 / (abs(i - column) + 1);
            }
        }
    }

    int make_move(int* column_move) override {
        //look at new at
        bool empty = true;
        for (size_t i = 0; i < 5; i++) {
            empty = empty && items->at(i) == nullptr;
            if (items->at(i) == nullptr) {
                //place
                //*column_move = random_int(1, columns);
                *column_move = draw_from_distribution(this->generate_probs());
                //this should draw how the prob vector instead
            } else {
                if (items->at(i) != nullptr) {
                    items->at(i)->update();
                }
            }
        }
        done = true;
        return -1;
    }

};


#endif
