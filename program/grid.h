#ifndef GRID_H_
#define GRID_H_

#include <string>
#include <vector>
#include <iostream>

class Grid {
    std::vector<std::string> grid;
    int rows, columns;
    int size;

    public:

    Grid(int rows, int columns);
    void print_grid() const;

    std::string& operator()(int row, int column);
    const std::string& operator()(int row, int column) const;
};

inline Grid::Grid(int rows, int columns)
    : rows(rows), columns(columns), size(rows * columns) {
    grid.resize(rows*columns);
    for (int i = 0; i < size; i++) {
        grid[i] = " ";
    }
    this->operator()(rows - 1, 10) = "c";
}

inline void Grid::print_grid() const {
    for (int i = 0; i < size; i++) {
        if (i % columns == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << grid[i] << " ";
    }
    std::cout << std::endl;
}

inline std::string& Grid::operator()(int row, int column) {
    return grid[row * columns + column];
}

inline const std::string& Grid::operator()(int row, int column) const {
    return grid[row * columns + column];
}

#endif
