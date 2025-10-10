#ifndef OWNER_H_
#define OWNER_H_

class Owner {

    protected:

    int max_health = 1;
    int score = 0;
    Owner* opponent;

    public:

    Owner(Owner* opponent = nullptr) : opponent(opponent) {}

    ~Owner() {}

    virtual int get_max_health() const {
        return max_health;
    }

    virtual int get_score() const {
        return score;
    }

    virtual Owner* return_opponent() const {
        return opponent;
    }

    virtual void adjust_score(int n) {
        score = score + n;
    }


};

#endif
