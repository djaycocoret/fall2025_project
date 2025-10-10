#ifndef AI_H_
#define AI_H_

#include "owner.h"


class AI : public Owner {
    public:

    AI() : Owner() {
        max_health = 3;
    }

    ~AI() {}
};


#endif
