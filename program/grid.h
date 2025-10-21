#ifndef GRID_H_
#define GRID_H_

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "sleep.h"
#include "move.h"


template <typename T> //uses a template such that it can store any kind of object
class Grid {

    std::vector<T*> grid; //a vector of pointers to an object instead of us

    int rows, cols;
    int size;

    public:

    Grid(int rows, int cols) : rows(rows), cols(cols) {
        size = rows * cols;
        grid.resize(size, nullptr);
    }

    Grid() {}

    ~Grid() {
        for (int i = 0; i < size; i++) {
            if (grid[i] != nullptr) {
                delete grid[i];
            }
        }
    }

    int get_cols() const {
        return cols;
    }

    int get_rows() const {
        return rows;
    }

    void print_grid() const { //maybe add an object that contains all game information as input?
        std::cout << "  ";
        for (int i = 0; i < cols; i ++) {
            std::cout << std::right << std::setw(4) <<  i << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < size; i++) {
            if (i % cols == 0) {
                if (i != 0) {
                    std::cout << std::right << std::setw(2) <<((int)i / cols - 1);
                    std::cout << std::endl;
                }
                    std::cout << std::right << std::setw(2) <<((int)i / cols);
            }
            if (grid[i] != nullptr) {
                std::cout << std::right << std::setw(4) << grid[i]->get_id() << " ";
            } else {
                std::cout<< std::right << std::setw(4) << " " << " ";
            }
        }
        std::cout << std::right << std::setw(2) <<(rows - 1);
        std::cout << std::endl;
    }

    void print_index_grid() const { //maybe add an object that contains all game information as input?
        std::cout << "  ";
        for (int i = 0; i < cols; i ++) {
            std::cout << std::right << std::setw(4) <<  i << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < size; i++) {
            if (i % cols == 0) {
                if (i != 0) {
                    std::cout << std::right << std::setw(2) <<((int)i / cols - 1);
                    std::cout << std::endl;
                }
                    std::cout << std::right << std::setw(2) <<((int)i / cols);
            }
            if (grid[i] != nullptr) {
                std::cout << std::right << std::setw(4) << grid[i]->get_index() << " ";
            } else {
                std::cout<< std::right << std::setw(4) << " " << " ";
            }
        }
        std::cout << std::right << std::setw(2) <<(rows - 1);
        std::cout << std::endl;
    }

    T* const operator()(int row, int col) const { //row major indexing for grid
        return grid[row * cols + col];    }

    T*& operator()(int row, int col) { //column major indexing for grid
        return grid[row * cols + col];
    }

    bool move_object(Move& move) {
        if (move.row_new < 0 || move.row_new >= rows || move.col_new < 0 || move.col_new >= cols) {
            return false;
        } else if (this->operator()(move.row_new, move.col_new) == nullptr) {
            this->operator()(move.row_new, move.col_new) = this->operator()(move.row, move.col);
            this->operator()(move.row, move.col) = nullptr;
            return true;
        } else {
            return false;
        }
    }

    void delete_object(int row, int col) {
        this->operator()(row, col) = nullptr;
    }
};


#endif
