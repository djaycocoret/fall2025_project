#ifndef OWNER_H_
#define OWNER_H_


#include <iostream>
#include <vector>
template<typename T>
class Owner {

    std::vector<T> items;

    protected:

    int max_health = 1;
    int score = 0;
    Owner* opponent;

    public:

    Owner(Owner<T>* opponent = nullptr) : opponent(opponent) {}

    ~Owner() {}

    virtual int get_max_health() const {
        return max_health;
    }

    virtual void set_opponent(Owner<T>* opp) {
        opponent = opp; //maybe make this a vector for dynamical
    }

    virtual int get_score() const {
        return score;
    }

    virtual Owner<T>* return_opponent() const {
        return opponent;
    }

    virtual void adjust_score(int n) {
        score = score + n;
    }

    virtual void add_object(T obj) { //unsafe must find way to delete object from items, since it also gets deleted by the grid
        items.push_back(obj);
    }

    void print_objects() {
        for (const auto& element : items) {
                std::cout << element->get_position() << " ";
            }
    }


};

#endif
