#ifndef MOVE_H_
#define MOVE_H_

struct Move {
    int index_owner;

    int row;
    int col;
    int row_new;
    int col_new;

    int dmg;

    bool remove_obj = false;
    bool new_obj = false;
    bool moved_bool = false; //moved / done move
    bool movement_bool = false;
    bool shoot_bool = false;

};

struct Info {
    int rows;
    int cols;
    int wave;
    int score;
    int highscore;
    int health;
    bool game_over = false;
};

#endif
