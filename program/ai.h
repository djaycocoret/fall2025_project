#ifndef AI_H_
#define AI_H_

#include "owner.h"
#include "grid_object.h"
#include "sleep.h"
#include <iostream>


class AI : public Owner<GO*> {
    public:

    AI() : Owner<GO*>() {
        max_health = 3;
        name = "AI";
    }

    ~AI() {}

    int make_move(int* column_move, int* index) override {
        *index = -1;
        for (size_t i = 0; i < 5; i++) {
            if (items->at(i) == nullptr) {
                //place
                int columns = 10; // hardcoded for now
                *column_move = random_int(1, columns);
                *index = i;
            } else {
                if (items->at(i) != nullptr) {
                    items->at(i)->update();
                }
            }
        }
        return -1;
    }

};


#endif
