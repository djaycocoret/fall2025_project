#ifndef OWNER_WRAPPER_H_
#define OWNER_WRAPPER_H_

#include "owner.h"
#include "grid_object.h"
#include <vector>

//have to make wrapper because of recursive calls

class OW : public Owner {

    std::vector<GO*> items;

    public:

    OW(OW* opp = nullptr) : Owner(opp) {}
};

#endif
