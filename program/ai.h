#ifndef AI_H_
#define AI_H_

#include "owner.h"
#include "grid_object.h"


class AI : public Owner<GO*> {
    public:

    AI() : Owner<GO*>() {
        max_health = 3;
    }

    ~AI() {}

};


#endif
