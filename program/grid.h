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

    std::vector<T*> grid; //a vector of pointers to an object.

    int rows, cols;
    int size;

    public:

    Grid(int rows, int cols) : rows(rows), cols(cols) {
        size = rows * cols;
        grid.resize(size, nullptr); //resize the grid vecor to rows * columns, filling with nullptr
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

    void print_grid() const { //dumbest way to print the grid honestly (oops)
        std::cout << "  ";
        for (int i = 0; i < cols; i ++) {
            std::cout << std::right << std::setw(4) <<  i << " ";
        }
        std::cout << std::endl;

        //below prints the row numbers of the grid (hideos)
        for (int i = 0; i < size; i++) { //so this is the loop that prints out the whole grid
            if (i % cols == 0) { //start of a row
                if (i != 0) { //if not on the first row
                    std::cout << std::right << std::setw(2) <<((int)i / cols - 1);
                    std::cout << std::endl;
                }

                    std::cout << std::right << std::setw(2) <<((int)i / cols);


            }
            if (grid[i] != nullptr) {
                //below gets the id, which is assigned to the grid_object
                std::cout << std::right << std::setw(4) << grid[i]->get_id() << " ";
            } else {
                //above, but empty space instead of GO->get_id()
                std::cout<< std::right << std::setw(4) << " " << " ";
            }
        }

        std::cout << std::right << std::setw(2) <<(rows - 1); //row number on the right side
        std::cout << std::endl;
    }

    void print_index_grid() const { //same as above, just with index instead of character. (not good to copy, paste and edit code like this. but it works.)
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

    T*& operator()(int row, int col) { //by reference (can change to nullptr)
        return grid[row * cols + col];
    }

    bool move_object(Move& move) {
        if (move.row_new < 0 || move.row_new >= rows || move.col_new < 0 || move.col_new >= cols) {
            return false;
        } else if (this->operator()(move.row_new, move.col_new) == nullptr) { //checks if place is free
            this->operator()(move.row_new, move.col_new) = this->operator()(move.row, move.col); //copies the pointer to new place
            this->operator()(move.row, move.col) = nullptr; //assigns nullptr to old place
            return true; //returns true if object has moved
        } else {
            return false;
        }
    }

    void delete_object(int row, int col) {
        this->operator()(row, col) = nullptr;
    }
};


#endif
