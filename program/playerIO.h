#ifndef PLAYER_H_
#define PLAYER_H_

#include "owner.h"


class Player : public Owner {
    public:

    Player(Owner* opp) : Owner(opp) {
    }

    ~Player() {}
};


#endif
