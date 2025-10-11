#ifndef OWNER_H_
#define OWNER_H_


#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
class Owner {


    bool game_over;

    protected:
    std::string name = "default";
    std::vector<T>* items = new std::vector<T>;

    protected:

    int max_health = 1;
    int score = 0;
    Owner<T>* opponent;

    public:

    Owner(Owner<T>* opponent = nullptr) : opponent(opponent) {
        game_over = false;
        items->resize(6);
    }

    ~Owner() {
        for (size_t i = 0; i < items->size(); i++) {
            items->at(i) = nullptr;
        }
        delete items;
    }

    T get_items(int i) {
        size_t id = i;
        return items->at(id);
    }

    void set_item(T obj, int index) {
        //check if in bounds
        size_t i = index;
        items->at(i) = obj;
    }

    void delete_from_items(int index) {
        items->at(index) = nullptr;
    }

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


    virtual int make_move(int* column_move, int* index) {
        for (size_t i = 0; i < items->size(); i++) {
            if (items->at(i) != nullptr) {
                items->at(i)->update();
            }
        }
        return 1;
    }

    virtual std::vector<int> make_move_() {
        return std::vector<int> {0};
    }

    void print_objects() {
        std::cout << std::left << std::setw(7) << this->name << ": ";
        for (size_t i = 0 ; i < 5; i++) {
            if (items->at(i) != nullptr) {
                std::cout << items->at(i)->get_position() << " ";
            }
        }
        std::cout << std::endl;
    }

    bool operator!=(const Owner& other) const {
        return true;
    }

    virtual void set_game_over(bool val) {
        game_over = val;
    }

    virtual bool get_game_over() const {
        return game_over;
    }
};

#endif
