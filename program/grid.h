#ifndef GRID_H_
#define GRID_H_

#include <string>
#include <vector>
#include <iostream>
#include "grid_object.h"
#include <iomanip>
#include "owner.h"
#include "sleep.h"


class Grid {

    public:
    std::vector<GO*> grid;
    int rows, columns;
    int size;
    int highscore;

    Grid(int rows, int columns);

    ~Grid() { //deconstructor
        for (int i = 0; i < size; i++) {
            if (grid[i] != nullptr) {
                delete grid[i];
            }
        }
    }

    void print_grid(Owner<GO*>* owner, bool clear_output, int* wave, std::vector<double>* prob_output) const;

    GO*& operator()(int row, int column);
    const GO* operator()(int row, int column) const;

    void place(int row, int column, GO*);

    GO*& id(int row, int column);
    bool move(int row, int column, int row_new, int column_new);
    void delete_object(int row, int column);
    void give_highscore(int& highscore) {
        this->highscore = highscore;
    }
    void update() {
        for (int i = 0; i < size; i++) {
            if (grid[i] != nullptr) {
                //std::cout << "(" << (int)i/columns + 1<< ", " << i % columns + 1 << ")";
                grid[i]->update();
            }
        }
        for (int i = 0; i < size; i++) {
            if (grid[i] != nullptr) {
                grid[i]->end_turn();
            }
        }
    }

    void place_ai(int column, GO* obj);
};

inline void Grid::place_ai(int column, GO* obj) {
    this->place(1, column, obj);
}

inline Grid::Grid(int rows, int columns)
    : rows(rows), columns(columns), size(rows * columns) {
    grid.resize(rows*columns, nullptr);
}

inline bool Grid::move(int row, int column, int row_new, int column_new) {
    if (row_new <= 0 || row_new > rows || column_new <= 0 || column_new > column) {
        std::cout << "something wrong" << std::endl;
        return false;
    }
    //does not move if it cannot move
    if (this->operator()(row_new, column_new) == nullptr) {
        this->operator()(row_new, column_new) = this->operator()(row, column);
        this->operator()(row, column) = nullptr;
        return true;
    } else {
        return false;
    }
}

inline void Grid::delete_object(int row, int column) {
    GO*& object = this->operator()(row, column);
    delete object;
    this->operator()(row, column) = nullptr;
}

inline void Grid::print_grid(Owner<GO*>* owner=nullptr, bool clear_output = true, int* wave = nullptr, std::vector<double>* prob_output = nullptr) const {
    if (clear_output) {
        system("clear");
    }
    std::cout << "health: " << this->operator()(rows,(int)columns/2)->get_health() << "/100" << " ";
    if (owner != nullptr) {
        std::cout << "points: " << owner->get_score() << " ";
    } else {
            std::cout << "points: " << "E" << " ";
    }
    std::cout << "high score: " << highscore << " ";
    if (wave != nullptr) {
        std::cout << "wave: " << *wave << " ";
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i < columns; i ++) {
        std::cout << std::right << std::setw(4) <<  std::fixed << std::setprecision(2) << prob_output->at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i < columns; i ++) {
        std::cout << std::right << std::setw(4) <<  i + 1 << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        if (i % columns == 0) {
            if (i != 0) {
                std::cout << std::right << std::setw(2) <<((int)i / columns);
              std::cout << std::endl;
            }
            std::cout << std::right << std::setw(2) <<((int)i / columns) + 1;
        }
        if (grid[i] != nullptr) {
            std::cout << std::right << std::setw(4) << grid[i]->id << " ";
        } else {
            std::cout<< std::right << std::setw(4) << " " << " ";
        }
    }
    std::cout << std::endl;
}


inline void Grid::place(int row, int column, GO* object) {
    if (row <= rows && column <= columns && row >= 0 && columns >= 0) {
        this->operator()(row, column) = object;
    }
}

inline GO*& Grid::operator()(int row, int column) {
    if (row <= rows && column <= columns && row >= 0 && columns >= 0) {
        return grid[(row-1) * columns + (column-1)];
    } else {
        return grid[0];
    }
}

inline GO*& Grid::id(int row, int column) {
    if (row <= rows && column <= columns && row >= 0 && columns >= 0) {
        return grid[(row) * columns + (column)];
    } else {
        return grid[0];
    }
}

inline const GO* Grid::operator()(int row, int column) const {
    return grid[(row-1) * columns + (column-1)];
}

#endif
