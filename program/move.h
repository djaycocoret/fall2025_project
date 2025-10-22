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
    bool reached_castle = false;

};

struct Info {
    int rows, cols;
    int wave, health;
    int enemies_health = 3;
    int enemies_placed = 0;
    int enemies_placed_total = 0;
    int score, highscore;
    bool game_over = false;
};

class Difficulty {
    public:
    //ai stuff
    double learning_rate;
    int base_speed;
    int base_health;

    //player stuff
    int start_range_tower;
    int upgrade_range_tower_length;
    int base_power;

    Difficulty() {
        learning_rate = 0.5;
        base_speed = 1;
        base_health = 3;

        start_range_tower = 2;
        upgrade_range_tower_length = 1;
        base_power = 1;
    }

    Difficulty(int n) {
        if (n > 0 && n < 4) {
            if (n == 1) {
                learning_rate = 0.3;
                base_speed = 1;
                base_health = 2;

                start_range_tower = 3;
                upgrade_range_tower_length = 2;
                base_power = 3;
            } else if (n == 2) {
                learning_rate = 0.5;
                base_speed = 1;
                base_health = 3;

                start_range_tower = 3;
                upgrade_range_tower_length = 1;
                base_power = 2;
            } else if (n == 3) {
                learning_rate = 0.8;
                base_speed = 2;
                base_health = 3;

                start_range_tower = 2;
                upgrade_range_tower_length = 1;
                base_power = 1;
            }
        }
    }
};

#endif
