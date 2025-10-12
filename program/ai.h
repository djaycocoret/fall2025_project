#ifndef AI_H_
#define AI_H_

#include "owner.h"
#include "grid_object.h"
#include "sleep.h"
#include <cmath>
#include <iostream>

class AI : public Owner<GO*> {
    public:

    double learning_rate = 0.5;
    bool done = false;


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

    int make_move(int* column_move) override {
        //look at new at
        bool empty = true;
        for (size_t i = 0; i < 5; i++) {
            empty = empty && items->at(i) == nullptr;
            if (items->at(i) == nullptr) {
                //place
                *column_move = random_int(1, columns);
                //this should draw how the prob vector instead
            } else {
                if (items->at(i) != nullptr) {
                    items->at(i)->update();
                }
            }
        }
        done = true;
        //this is where you can finalise the move
        prob[*column_move - 1] = prob[*column_move - 1] - learning_rate;
        return -1;
    }

};


#endif
