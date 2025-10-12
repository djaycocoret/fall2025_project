#ifndef MOVE_H_
#define MOVE_H_

struct Move {
    int row;
    int column;
    bool update = false;
    bool upgrade = false;
    bool delete_ = false;
    bool place = false;
};

#endif
