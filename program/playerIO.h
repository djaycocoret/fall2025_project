#ifndef PLAYER_H_
#define PLAYER_H_

#include "owner.h"
#include "grid_object.h"


class Player : public Owner<GO*> {
    public:

    Player(Owner<GO*>* opp) : Owner(opp) {
    }

    ~Player() {}
};


#endif
