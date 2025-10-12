#ifndef PLAYER_H_
#define PLAYER_H_

#include "owner.h"
#include "grid_object.h"



class Player : public Owner<GO*> {
    public:

    Player(Owner<GO*>* opp) : Owner(opp) {
        name = "player";
    }

    ~Player() {}

    int make_move(int* column_move) {
        Owner<GO*>::make_move(column_move);

        return -1;
    }
};


#endif
